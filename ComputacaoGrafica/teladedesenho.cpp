// Em teladedesenho.cpp
#include "teladedesenho.h"
#include <QPainter>
#include <QPen>
#include <cmath>
#include <algorithm> // Para std::min

TelaDeDesenho::TelaDeDesenho(QWidget *parent) : QWidget(parent) {
    // A câmera agora é gerenciada pela MainWindow
}

void TelaDeDesenho::setDisplayFile(QVector<ObjetoVirtual> *ptr_df) {
    this->displayFile_ptr = ptr_df;
}

void TelaDeDesenho::setIndiceDaWindow(int indice) {
    this->indiceDaWindow = indice;
}

Matriz TelaDeDesenho::calcularMatrizDeVisualizacao() const {
    // --- Proteção ---
    if (!displayFile_ptr || indiceDaWindow == -1 ||
        indiceDaWindow >= displayFile_ptr->size())
    {
        return Matriz::criarIdentidade();
    }

    // --- Etapa 1: Ler as propriedades da Câmera do Objeto Window ---
    const ObjetoVirtual& windowObj = (*displayFile_ptr)[indiceDaWindow];
    const Ponto& cameraPos = windowObj.camera_centro;
    double zoom = windowObj.camera_zoom;
    double rotX = windowObj.camera_rotX;
    double rotY = windowObj.camera_rotY;

    // --- Etapa 2: Definir a Viewport ---
    double vp_x_min = MARGEM_VIEWPORT;
    double vp_y_min = MARGEM_VIEWPORT;
    double vp_largura = this->width() - 2 * MARGEM_VIEWPORT;
    double vp_altura = this->height() - 2 * MARGEM_VIEWPORT;

    if (vp_largura < 1 || vp_altura < 1) return Matriz::criarIdentidade();

    // --- Etapa 3: Matriz de Viewport (SCN -> Tela) ---
    // (Esta é a versão CORRIGIDA que evita o "achatamento")
    double menorDimensaoVP = std::min(vp_largura, vp_altura);
    Matriz S_vp = Matriz::criarMatrizEscala(menorDimensaoVP / 2.0, -menorDimensaoVP / 2.0, 1.0);
    Matriz T_vp = Matriz::criarMatrizTranslacao(vp_x_min + vp_largura / 2.0, vp_y_min + vp_altura / 2.0, 0);
    Matriz M_viewport = T_vp * S_vp;

    // --- Etapa 4: Matriz de Projeção Ortogonal (Câmera -> SCN) ---
    double r = 1.0 / zoom;
    double l = -r;
    double t = 1.0 / zoom;
    double b = -r;
    double n = 1.0;
    double f = 1000.0;

    Matriz M_proj;
    M_proj.dados[0][0] = 2.0 / (r - l);
    M_proj.dados[1][1] = 2.0 / (t - b);
    M_proj.dados[2][2] = -2.0 / (f - n);
    M_proj.dados[3][3] = 1.0;
    M_proj.dados[0][3] = -(r + l) / (r - l);
    M_proj.dados[1][3] = -(t + b) / (t - b);
    M_proj.dados[2][3] = -(f + n) / (f - n);

    // --- Etapa 5: Matriz de Câmera (Mundo -> Câmera) ---
    Matriz R_cam = Matriz::criarMatrizRotacaoY(-rotY) * Matriz::criarMatrizRotacaoX(-rotX);
    Matriz T_cam = Matriz::criarMatrizTranslacao(-cameraPos.x(), -cameraPos.y(), -cameraPos.z());
    Matriz M_camera = R_cam * T_cam;

    // --- Etapa Final: Matriz Composta ---
    return M_viewport * M_proj * M_camera;
}

// --- O seu paintEvent() ---
// (Substitua pela versão com QPainter::setClipRect() da nossa conversa anterior,
// ela não precisa de mais nenhuma alteração e funcionará perfeitamente com esta nova matriz)
void TelaDeDesenho::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black);

    QRectF viewportRect(MARGEM_VIEWPORT, MARGEM_VIEWPORT,
                        this->width() - 2 * MARGEM_VIEWPORT,
                        this->height() - 2 * MARGEM_VIEWPORT);

    painter.setClipRect(viewportRect); // Ativa o clipping

    if (!displayFile_ptr || displayFile_ptr->isEmpty()) return;

    Matriz M_final = calcularMatrizDeVisualizacao();

    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
        // NÃO desenha a própria câmera
        if (objeto.nome == "#WINDOW_CAMERA") continue;

        painter.setPen(QPen(objeto.cor, 1));

        for (const Face &face : objeto.faces) {
            for (int i = 0; i < face.indicesVertices.size(); ++i) {
                int indice1 = face.indicesVertices[i];
                int indice2 = face.indicesVertices[(i + 1) % face.indicesVertices.size()];

                if (indice1 >= objeto.vertices.size() || indice2 >= objeto.vertices.size()) {
                    continue;
                }

                Ponto v1_mundo = objeto.vertices[indice1];
                Ponto v2_mundo = objeto.vertices[indice2];
                Ponto p1_tela = M_final * v1_mundo;
                Ponto p2_tela = M_final * v2_mundo;

                painter.drawLine(QPointF(p1_tela.x(), p1_tela.y()), QPointF(p2_tela.x(), p2_tela.y()));
            }
        }
    }

    painter.setClipping(false);
    painter.setPen(QPen(Qt::gray, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(viewportRect);
}
