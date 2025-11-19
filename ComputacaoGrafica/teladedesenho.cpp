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

Matriz TelaDeDesenho::calcularMatrizDeVisualizacao() const {
    // Esta função serve apenas para calcular a Projeção e Viewport.
    // A Matriz de Câmera será calculada separadamente no paintEvent para permitir o Culling.
    return Matriz::criarIdentidade();
}

void TelaDeDesenho::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black);

    // --- 1. Configurar Viewport (Recorte de Tela) ---
    double margem = MARGEM_VIEWPORT;
    QRectF viewportRect(margem, margem,
                        this->width() - 2 * margem,
                        this->height() - 2 * margem);
    painter.setClipRect(viewportRect);

    if (!displayFile_ptr || indiceDaWindow == -1 || indiceDaWindow >= displayFile_ptr->size()) return;

    // --- 2. Ler Propriedades da Câmera ---
    const ObjetoVirtual& windowObj = (*displayFile_ptr)[indiceDaWindow];
    const Ponto& cameraPos = windowObj.camera_centro;
    double zoom = windowObj.camera_zoom;
    double rotX = windowObj.camera_rotX;
    double rotY = windowObj.camera_rotY;
    double rotZ = windowObj.camera_rotZ;

    // --- 3. Construir Matriz de Câmera (VIEW Matrix) ---
    Matriz R_cam = Matriz::criarMatrizRotacaoZ(-rotZ) * Matriz::criarMatrizRotacaoX(-rotX) * Matriz::criarMatrizRotacaoY(-rotY);
    Matriz T_cam = Matriz::criarMatrizTranslacao(-cameraPos.x(), -cameraPos.y(), -cameraPos.z());
    Matriz M_view = R_cam * T_cam;

    // --- 4. Construir Matrizes de Projeção e Viewport ---
    double vp_w = viewportRect.width();
    double vp_h = viewportRect.height();
    double aspect = (vp_h > 0) ? (vp_w / vp_h) : 1.0;
    double n = 1.0;     // Plano Próximo (Near)
    double f = 2000.0;  // Plano Distante (Far)

    Matriz M_proj;
    if (projecaoAtual == ProjecaoTipo::ORTOGONAL) {
        // Ortogonal corrigida
        double r = (1.0 / zoom) * (vp_w / std::min(vp_w, vp_h));
        double t = (1.0 / zoom) * (vp_h / std::min(vp_w, vp_h));

        M_proj = Matriz::criarIdentidade();
        M_proj.dados[0][0] = 1.0 / r;
        M_proj.dados[1][1] = 1.0 / t;
        M_proj.dados[2][2] = -2.0 / (f - n);
        M_proj.dados[2][3] = -(f + n) / (f - n);
    } else {
        // Perspectiva
        M_proj = Matriz::criarMatrizPerspectiva(60.0, aspect, n, f);
    }

    Matriz M_viewport = Matriz::criarMatrizTranslacao(margem + vp_w/2, margem + vp_h/2, 0) * Matriz::criarMatrizEscala(vp_w/2, -vp_h/2, 1);

    // Matriz Final (sem a Câmera, pois aplicaremos a câmera antes para fazer o Culling)
    Matriz M_proj_vp = M_viewport * M_proj;

    // --- 5. Desenhar Objetos com Culling ---
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

                // A. Transforma para o Espaço da Câmera
                Ponto v1_view = M_view * v1_mundo;
                Ponto v2_view = M_view * v2_mundo;

                // B. CULLING
                // Se o ponto estiver atrás do plano próximo (z > -n), ignoramos.
                // (Nota: No espaço da câmera, a câmera olha para -Z. Então objetos visíveis têm Z negativo).
                if (v1_view.z() > -n || v2_view.z() > -n) {
                    continue; // Ignora esta linha se algum ponto estiver atrás da câmera
                }

                // C. Projeta para a Tela
                Ponto p1_tela = M_proj_vp * v1_view;
                Ponto p2_tela = M_proj_vp * v2_view;

                painter.drawLine(QPointF(p1_tela.x(), p1_tela.y()), QPointF(p2_tela.x(), p2_tela.y()));
            }
        }
    }

    // Desenha borda
    painter.setClipping(false);
    painter.setPen(QPen(Qt::gray, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(viewportRect);
}
