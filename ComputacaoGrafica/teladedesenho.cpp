#include "teladedesenho.h"
#include <QPainter>
#include <QPen>
#include <cmath>

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
    // 1. Matriz de Viewport (SCN -> Tela)
    double vp_x_min = MARGEM_VIEWPORT;
    double vp_y_min = MARGEM_VIEWPORT;
    double vp_largura = this->width() - 2 * MARGEM_VIEWPORT;
    double vp_altura = this->height() - 2 * MARGEM_VIEWPORT;

    Matriz S_vp = Matriz::criarMatrizEscala(vp_largura / 2.0, -vp_altura / 2.0, 1.0); // Inverte Y
    Matriz T_vp = Matriz::criarMatrizTranslacao(vp_x_min + vp_largura / 2.0, vp_y_min + vp_altura / 2.0, 0);
    Matriz M_viewport = T_vp * S_vp;

    // 2. Matriz de Projeção Ortogonal
    // Define o "cubo" de visualização no espaço da câmera.
    double proj_largura = (vp_largura / zoom);
    double proj_altura = (vp_altura / zoom);
    double r = proj_largura / 2.0;
    double l = -r;
    double t = proj_altura / 2.0;
    double b = -t;
    double n = 1.0;    // Near plane
    double f = 1000.0; // Far plane (distância de visualização)

    Matriz M_proj;
    M_proj.dados[0][0] = 2.0 / (r - l);
    M_proj.dados[1][1] = 2.0 / (t - b);
    M_proj.dados[2][2] = -2.0 / (f - n);
    M_proj.dados[3][3] = 1.0;
    M_proj.dados[0][3] = -(r + l) / (r - l);
    M_proj.dados[1][3] = -(t + b) / (t - b);
    M_proj.dados[2][3] = -(f + n) / (f - n);

    // 3. Matriz de Câmera (Mundo -> Câmera)
    Matriz R_cam = Matriz::criarMatrizRotacaoY(-rotY) * Matriz::criarMatrizRotacaoX(-rotX);
    Matriz T_cam = Matriz::criarMatrizTranslacao(-cameraPos.x(), -cameraPos.y(), -cameraPos.z());
    Matriz M_camera = R_cam * T_cam;

    // 4. Matriz Final
    // Transforma do Mundo -> Câmera -> Projeção -> Viewport
    return M_viewport * M_proj * M_camera;
}

void TelaDeDesenho::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::black); // Fundo preto

    if (!displayFile_ptr || displayFile_ptr->isEmpty()) return;

    // 1. Obter a matriz de transformação final
    Matriz M_final = calcularMatrizDeVisualizacao();

    // 2. Desenhar todos os objetos
    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
        painter.setPen(QPen(objeto.cor, 1)); // Define a cor do wireframe

        // 3. Iterar sobre as FACES do objeto
        for (const Face &face : objeto.faces) {

            // 4. Desenhar cada ARESTA da face
            for (int i = 0; i < face.indicesVertices.size(); ++i) {
                int indice1 = face.indicesVertices[i];
                int indice2 = face.indicesVertices[(i + 1) % face.indicesVertices.size()]; // Próximo, com wrap-around

                // 5. Garantir que os índices são válidos
                if (indice1 >= objeto.vertices.size() || indice2 >= objeto.vertices.size()) {
                    continue; // Pula esta aresta se os dados estiverem corrompidos
                }

                // 6. Pegar os vértices 3D do mundo
                Ponto v1_mundo = objeto.vertices[indice1];
                Ponto v2_mundo = objeto.vertices[indice2];

                // 7. Transformar para a tela
                Ponto p1_tela = M_final * v1_mundo;
                Ponto p2_tela = M_final * v2_mundo;

                // 8. Desenhar a linha 2D
                painter.drawLine(QPointF(p1_tela.x(), p1_tela.y()), QPointF(p2_tela.x(), p2_tela.y()));
            }
        }
    }

    // 9. Desenhar a borda da viewport (como antes)
    painter.setPen(QPen(Qt::gray, 1));
    painter.setBrush(Qt::NoBrush);
    QRectF viewportRect(MARGEM_VIEWPORT, MARGEM_VIEWPORT, this->width() - 2 * MARGEM_VIEWPORT, this->height() - 2 * MARGEM_VIEWPORT);
    painter.drawRect(viewportRect);
}
