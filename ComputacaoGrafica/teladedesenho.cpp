// Em teladedesenho.cpp
#include "teladedesenho.h"
#include <QPainter>
#include <QPen>
#include <QWheelEvent>
#include <cmath>
#include <algorithm>

TelaDeDesenho::TelaDeDesenho(QWidget *parent) : QWidget(parent) {}

void TelaDeDesenho::setDisplayFile(QVector<ObjetoVirtual> *ptr_df) {
    this->displayFile_ptr = ptr_df;
}

void TelaDeDesenho::setIndiceDaWindow(int indice) {
    this->indiceDaWindow = indice;
}

void TelaDeDesenho::setProjecao(ProjecaoTipo tipo) {
    this->projecaoAtual = tipo;
    update();
}

void TelaDeDesenho::wheelEvent(QWheelEvent *event) {
    double delta = event->angleDelta().y();
    double fator = (delta > 0) ? 1.1 : 0.9;
    emit zoomRequisitado(fator);
    event->accept();
}

// Função auxiliar para cortar linhas no Espaço da Câmera (View Space)
// Retorna 'false' se a linha estiver totalmente atrás da câmera.
bool clipLineZ(Ponto &p1, Ponto &p2, double nearPlane) {
    // Nota: No View Space, a câmera olha para -Z.
    // O Near Plane está em Z = -nearPlane.
    // Pontos visíveis têm Z <= -nearPlane (mais negativos).
    // Pontos invisíveis (atrás da câmera) têm Z > -nearPlane.

    double zLimit = -nearPlane;
    bool p1_visible = p1.z() <= zLimit;
    bool p2_visible = p2.z() <= zLimit;

    // 1. Caso Trivial: Ambos atrás da câmera -> Rejeita
    if (!p1_visible && !p2_visible) return false;

    // 2. Caso Trivial: Ambos visíveis -> Aceita sem mudanças
    if (p1_visible && p2_visible) return true;

    // 3. Caso Misto: Um dentro, um fora -> Precisamos cortar (Clip)
    // Calculamos o fator 't' onde a linha cruza o plano Z = zLimit
    double t = (zLimit - p1.z()) / (p2.z() - p1.z());

    // Calcula o novo ponto de interseção
    double newX = p1.x() + t * (p2.x() - p1.x());
    double newY = p1.y() + t * (p2.y() - p1.y());
    double newZ = zLimit; // Exatamente no plano

    // Substitui o ponto que estava fora pelo novo ponto cortado
    if (!p1_visible) {
        p1.setX(newX); p1.setY(newY); p1.setZ(newZ);
    } else {
        p2.setX(newX); p2.setY(newY); p2.setZ(newZ);
    }

    return true;
}

// 1. Calcula o código de região para um ponto (x, y, z)
// Estamos assumindo coordenadas normalizadas (NDC), onde o cubo visível é [-1, 1]
int TelaDeDesenho::computeOutCode(double x, double y, double z)
{
    int code = INSIDE;

    if (x < -1.0) code |= LEFT;
    else if (x > 1.0) code |= RIGHT;

    if (y < -1.0) code |= BOTTOM;
    else if (y > 1.0) code |= TOP;

    // Nota: Dependendo da matriz de projeção, o Z pode ser [0, 1] ou [-1, 1].
    // Na nossa matriz OpenGL padrão, é [-1, 1].
    if (z < -1.0) code |= NEAR;      // Perto demais (atrás da câmera)
    else if (z > 1.0) code |= FAR;   // Longe demais

    return code;
}

// 2. Algoritmo Cohen-Sutherland 3D
bool TelaDeDesenho::clipLine(double &x0, double &y0, double &z0,
                             double &x1, double &y1, double &z1)
{
    // Calcula os códigos iniciais dos dois pontos da reta
    int outcode0 = computeOutCode(x0, y0, z0);
    int outcode1 = computeOutCode(x1, y1, z1);
    bool accept = false;

    while (true) {
        if ((outcode0 | outcode1) == 0) {
            // Trivially Accept: Ambos os pontos estão dentro do cubo [-1, 1]
            accept = true;
            break;
        } else if (outcode0 & outcode1) {
            // Trivially Reject: Ambos estão fora na mesma região (ex: ambos à esquerda)
            // Não desenha nada.
            break;
        } else {
            // Caso complexo: A linha cruza a borda. Precisamos calcular a interseção.
            // Escolhe um ponto que esteja fora
            int outcodeOut = (outcode0 != 0) ? outcode0 : outcode1;

            double x, y, z;

            // Fórmulas de interseção de reta com planos
            // P = P0 + t * (P1 - P0)
            if (outcodeOut & FAR) { // Z = 1.0
                double t = (1.0 - z0) / (z1 - z0);
                x = x0 + (x1 - x0) * t;
                y = y0 + (y1 - y0) * t;
                z = 1.0;
            } else if (outcodeOut & NEAR) { // Z = -1.0
                double t = (-1.0 - z0) / (z1 - z0);
                x = x0 + (x1 - x0) * t;
                y = y0 + (y1 - y0) * t;
                z = -1.0;
            } else if (outcodeOut & TOP) { // Y = 1.0
                double t = (1.0 - y0) / (y1 - y0);
                x = x0 + (x1 - x0) * t;
                z = z0 + (z1 - z0) * t;
                y = 1.0;
            } else if (outcodeOut & BOTTOM) { // Y = -1.0
                double t = (-1.0 - y0) / (y1 - y0);
                x = x0 + (x1 - x0) * t;
                z = z0 + (z1 - z0) * t;
                y = -1.0;
            } else if (outcodeOut & RIGHT) { // X = 1.0
                double t = (1.0 - x0) / (x1 - x0);
                y = y0 + (y1 - y0) * t;
                z = z0 + (z1 - z0) * t;
                x = 1.0;
            } else if (outcodeOut & LEFT) { // X = -1.0
                double t = (-1.0 - x0) / (x1 - x0);
                y = y0 + (y1 - y0) * t;
                z = z0 + (z1 - z0) * t;
                x = -1.0;
            }

            // Atualiza o ponto que estava fora com as novas coordenadas cortadas
            if (outcodeOut == outcode0) {
                x0 = x; y0 = y; z0 = z;
                outcode0 = computeOutCode(x0, y0, z0);
            } else {
                x1 = x; y1 = y; z1 = z;
                outcode1 = computeOutCode(x1, y1, z1);
            }
        }
    }
    return accept;
}

Matriz TelaDeDesenho::calcularMatrizDeVisualizacao() const {
    // Esta função serve apenas para calcular a Projeção e Viewport.
    // A Matriz de Câmera será calculada separadamente no paintEvent para permitir o Culling.
    return Matriz::criarIdentidade();
}

void TelaDeDesenho::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black);

    double margem = MARGEM_VIEWPORT;
    double largura = this->width() - 2 * margem;
    double altura = this->height() - 2 * margem;
    QRectF viewportRect(margem, margem, largura, altura);
    painter.setClipRect(viewportRect);

    if (!displayFile_ptr || indiceDaWindow == -1 || indiceDaWindow >= displayFile_ptr->size()) return;

    // --- Ler Propriedades da Câmera ---
    const ObjetoVirtual& windowObj = (*displayFile_ptr)[indiceDaWindow];
    const Ponto& cameraPos = windowObj.camera_centro;
    double zoom = windowObj.camera_zoom;
    double rotX = windowObj.camera_rotX;
    double rotY = windowObj.camera_rotY;
    double rotZ = windowObj.camera_rotZ;

    // --- Matriz VIEW (Mundo -> Câmera) ---
    Matriz R_cam = Matriz::criarMatrizRotacaoZ(-rotZ) * Matriz::criarMatrizRotacaoX(-rotX) * Matriz::criarMatrizRotacaoY(-rotY);
    Matriz T_cam = Matriz::criarMatrizTranslacao(-cameraPos.x(), -cameraPos.y(), -cameraPos.z());
    Matriz M_view = R_cam * T_cam;

    // --- Matriz PROJECTION (Apenas a matriz, sem divisão ainda) ---
    double aspect = (altura > 0) ? (largura / altura) : 1.0;
    double n = 1.0;     // Near Plane
    double f = 2000.0;  // Far Plane

    Matriz M_proj;
    if (projecaoAtual == ProjecaoTipo::ORTOGONAL) {
        double dim = std::min(largura, altura);
        double r = (largura / dim) / zoom;
        double t = (altura / dim) / zoom;
        M_proj = Matriz::criarIdentidade();
        M_proj.dados[0][0] = 1.0 / r;
        M_proj.dados[1][1] = 1.0 / t;
        M_proj.dados[2][2] = -2.0 / (f - n);
        M_proj.dados[2][3] = -(f + n) / (f - n);
    } else {
        M_proj = Matriz::criarMatrizPerspectiva(60.0, aspect, n, f);
    }

    // --- Matriz VIEWPORT ---
    Matriz M_viewport = Matriz::criarMatrizTranslacao(margem + largura/2, margem + altura/2, 0) * Matriz::criarMatrizEscala(largura/2, -altura/2, 1);

    // --- PIPELINE DE DESENHO ---
    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
        if (objeto.nome == "#WINDOW_CAMERA") continue;

        painter.setPen(QPen(objeto.cor, 2));

        for (const Face &face : objeto.faces) {
            for (int i = 0; i < face.indicesVertices.size(); ++i) {
                int idx1 = face.indicesVertices[i];
                int idx2 = face.indicesVertices[(i + 1) % face.indicesVertices.size()];

                if (idx1 >= objeto.vertices.size() || idx2 >= objeto.vertices.size()) continue;

                Ponto v1_mundo = objeto.vertices[idx1];
                Ponto v2_mundo = objeto.vertices[idx2];

                // 1. Transformar para Espaço da Câmera (View Space)
                Ponto v1_view = M_view * v1_mundo;
                Ponto v2_view = M_view * v2_mundo;

                // 2. CLIPPING ROBUSTO (View Space Z-Clip)
                // Corta as linhas ANTES da projeção para evitar divisão por zero/negativo
                if (!clipLineZ(v1_view, v2_view, n)) {
                    continue; // Linha totalmente atrás da câmera
                }

                // 3. Projeção
                Ponto v1_clip = M_proj * v1_view;
                Ponto v2_clip = M_proj * v2_view;

                // 4. Divisão Perspectiva (Manual e Segura)
                // Agora é seguro dividir por W, pois o Clipping garantiu W > 0
                double w1 = v1_clip.dados[3][0];
                double w2 = v2_clip.dados[3][0];

                // Extrai coordenadas normalizadas (NDC)
                Ponto v1_ndc(v1_clip.x() / w1, v1_clip.y() / w1, v1_clip.z() / w1);
                Ponto v2_ndc(v2_clip.x() / w2, v2_clip.y() / w2, v2_clip.z() / w2);

                // 5. Viewport
                Ponto p1_tela = M_viewport * v1_ndc;
                Ponto p2_tela = M_viewport * v2_ndc;

                painter.drawLine(QPointF(p1_tela.x(), p1_tela.y()), QPointF(p2_tela.x(), p2_tela.y()));
            }
        }
    }

    painter.setClipping(false);
    painter.setPen(QPen(Qt::gray, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(viewportRect);
}
