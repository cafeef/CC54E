#include "teladedesenho.h"
#include <QPainter> // A classe QPainter é a "caneta" que usamos para desenhar

TelaDeDesenho::TelaDeDesenho(QWidget *parent) : QWidget(parent)
{
    // Define um fundo branco para a nossa área de desenho
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
}

void TelaDeDesenho::setDisplayFile(QVector<ObjetoVirtual> *df_ptr) {
    this->displayFile_ptr = df_ptr; // Guarda o ponteiro
}

void TelaDeDesenho::setWindow(Window *w) {
    this->window_ptr = w;
}

Matriz TelaDeDesenho::calcularMatrizDeVisualizacao() const
{
    // Obter dados da Window e Viewport (sem alterações aqui)
    Ponto centroWindow = window_ptr->getCentro();
    double anguloWindow = window_ptr->getAngulo();
    double larguraViewport = this->width();
    double alturaViewport = this->height();

    // --- AQUI ESTÁ A CORREÇÃO PARA A DEFORMAÇÃO ---

    // 1. Calcula os fatores de escala para cada eixo separadamente
    double fatorEscalaX = larguraViewport / window_ptr->getLargura();
    double fatorEscalaY = alturaViewport / window_ptr->getAltura(); // Usamos o valor positivo para comparar

    // 2. Escolhe o MENOR dos dois fatores. Isso garante que a cena inteira
    //    caiba na tela sem ser cortada e sem deformar.
    double fatorEscalaUniforme = std::min(fatorEscalaX, fatorEscalaY);

    // 3. Cria a matriz de escala usando o mesmo fator para ambos os eixos.
    //    A inversão do Y continua a ser necessária para o sistema de coordenadas da tela.
    Matriz S = Matriz::criarMatrizEscala(fatorEscalaUniforme, -fatorEscalaUniforme);

    // ---------------------------------------------------

    // O resto da função continua igual
    Matriz T = Matriz::criarMatrizTranslacao(-centroWindow.x(), -centroWindow.y());
    Matriz R = Matriz::criarMatrizRotacao(-anguloWindow);
    Matriz T_viewport = Matriz::criarMatrizTranslacao(larguraViewport / 2, alturaViewport / 2);

    return T_viewport * S * R * T;
}

void TelaDeDesenho::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this); // Inicia a "caneta" de desenho

    // Define uma caneta padrão (preta, 2 pixels de largura) para os desenhos
    QPen caneta;
    caneta.setColor(Qt::white);
    caneta.setWidth(5);
    painter.setPen(caneta);

    if (!displayFile_ptr || !window_ptr) return;

    // 1. Calcule a matriz de transformação (seu código está perfeito aqui)
    Matriz M_wv = calcularMatrizDeVisualizacao();

    // 2. Loop principal para aplicar a transformação em todos os pontos
    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
        // Cria a lista com os pontos já na coordenada da tela (seu código está perfeito aqui)
        QVector<QPointF> pontos_transformados;
        for (const Ponto &ponto_original : objeto.pontos) {
            Matriz ponto_na_tela_matriz = M_wv * ponto_original;
            pontos_transformados.append(QPointF(ponto_na_tela_matriz.getDados()[0][0],
                                                ponto_na_tela_matriz.getDados()[1][0]));
        }

        // Agora, usamos APENAS a lista 'pontos_transformados' para desenhar.

        if (pontos_transformados.isEmpty()) {
            continue; // Pula para o próximo objeto se não houver pontos
        }

        switch (objeto.tipo) {
        case TipoObjeto::Ponto: {
            caneta.setColor(objeto.cor);
            painter.setPen(caneta);
            painter.drawPoint(pontos_transformados.first());
            break;
        }

        case TipoObjeto::Reta: {
            caneta.setColor(objeto.cor);
            painter.setPen(caneta);
            if (pontos_transformados.size() == 2) {
                painter.drawLine(pontos_transformados[0], pontos_transformados[1]);
            }
            break;
        }

        case TipoObjeto::Poligono: {
            caneta.setColor(objeto.cor);
            painter.setPen(caneta);
            if (pontos_transformados.size() >= 3) {
                painter.drawPolygon(pontos_transformados);
            }
            break;
        }
        } // fim do switch
    } // fim do loop for
}
