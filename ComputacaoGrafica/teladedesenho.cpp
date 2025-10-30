#include "teladedesenho.h"
#include <QPainter>
#include <QPen>
#include <cmath>
#include <algorithm>

TelaDeDesenho::TelaDeDesenho(QWidget *parent) : QWidget(parent), cameraPos(0, 0, 500), zoom(1.0), rotX(0), rotY(0) {
    // Começamos com a câmera a olhar para a origem, afastada 500 unidades em Z.
}

void TelaDeDesenho::setDisplayFile(QVector<ObjetoVirtual> *ptr_df) {
    this->displayFile_ptr = ptr_df;
}

// --- Slots de Navegação 3D ---
void TelaDeDesenho::rotacionarCamera(double dx, double dy, double dz) {
    // Usaremos dx e dy para rotação (como arrastar o mouse)
    rotY += dx;
    rotX += dy;
    update();
}

void TelaDeDesenho::moverCamera(double dx, double dy, double dz) {
    // Isso será o "Pan"
    cameraPos.dados[0][0] += dx;
    cameraPos.dados[1][0] += dy;
    cameraPos.dados[2][0] += dz;
    update();
}

void TelaDeDesenho::aplicarZoom(double fator) {
    zoom *= fator;
    update();
}

// --- A Nova Pipeline de Renderização 3D ---
Matriz TelaDeDesenho::calcularMatrizDeVisualizacao() const {
    // --- Etapa 1: Definir a Viewport ---
    // (A área da tela para onde vamos desenhar)
    double vp_x_min = MARGEM_VIEWPORT;
    double vp_y_min = MARGEM_VIEWPORT;
    double vp_largura = this->width() - 2 * MARGEM_VIEWPORT;
    double vp_altura = this->height() - 2 * MARGEM_VIEWPORT;

    if (vp_largura < 1 || vp_altura < 1) return Matriz::criarIdentidade();

    // --- Etapa 2: Matriz de Viewport (SCN -> Tela) ---
    // Mapeia o SCN (-1 a 1) para a Viewport.
    // PARA EVITAR DISTORÇÃO: Usamos a MENOR dimensão da viewport como referência.
    // Isto garante que a escala (S_vp) seja UNIFORME.
    double menorDimensaoVP = std::min(vp_largura, vp_altura);
    Matriz S_vp = Matriz::criarMatrizEscala(menorDimensaoVP / 2.0, -menorDimensaoVP / 2.0, 1.0); // Inverte Y, escala uniforme
    Matriz T_vp = Matriz::criarMatrizTranslacao(vp_x_min + vp_largura / 2.0, vp_y_min + vp_altura / 2.0, 0); // Centra na viewport
    Matriz M_viewport = T_vp * S_vp;


    // --- Etapa 3: Matriz de Projeção Ortogonal (Câmera -> SCN) ---
    // Define o "cubo" de visualização no espaço da câmera.
    // O zoom é aplicado aqui, de forma uniforme.
    double r = 1.0 / zoom; // zoom=1 -> -1 a 1
    double l = -r;
    double t = 1.0 / zoom; // t = r para manter a proporção
    double b = -r;         // b = l para manter a proporção
    double n = 1.0;        // Near plane
    double f = 1000.0;     // Far plane

    Matriz M_proj;
    M_proj.dados[0][0] = 2.0 / (r - l);
    M_proj.dados[1][1] = 2.0 / (t - b);
    M_proj.dados[2][2] = -2.0 / (f - n);
    M_proj.dados[3][3] = 1.0;
    M_proj.dados[0][3] = -(r + l) / (r - l);
    M_proj.dados[1][3] = -(t + b) / (t - b);
    M_proj.dados[2][3] = -(f + n) / (f - n);


    // --- Etapa 4: Matriz de Câmera (Mundo -> Câmera) ---
    Matriz R_cam = Matriz::criarMatrizRotacaoY(-rotY) * Matriz::criarMatrizRotacaoX(-rotX);
    Matriz T_cam = Matriz::criarMatrizTranslacao(-cameraPos.x(), -cameraPos.y(), -cameraPos.z());
    Matriz M_camera = R_cam * T_cam;


    // --- Etapa Final: Matriz Composta ---
    return M_viewport * M_proj * M_camera;
}

void TelaDeDesenho::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black); // Fundo preto

    // --- CORREÇÃO DO CLIPPING ---
    // 1. Define o retângulo da nossa viewport
    QRectF viewportRect(MARGEM_VIEWPORT, MARGEM_VIEWPORT,
                        this->width() - 2 * MARGEM_VIEWPORT,
                        this->height() - 2 * MARGEM_VIEWPORT);

    // 2. Diz ao QPainter para SÓ desenhar dentro deste retângulo
    painter.setClipRect(viewportRect);
    // ----------------------------

    if (!displayFile_ptr || displayFile_ptr->isEmpty()) return;

    // 1. Obter a matriz de transformação final (agora corrigida)
    Matriz M_final = calcularMatrizDeVisualizacao();

    // 2. Desenhar todos os objetos
    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
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

    // 3. Desenhar a borda da viewport por último
    // Desativamos o clipping para que a própria borda possa ser desenhada
    painter.setClipping(false);
    painter.setPen(QPen(Qt::gray, 1));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(viewportRect);
}
