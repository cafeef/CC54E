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

void TelaDeDesenho::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this); // Inicia a "caneta" de desenho

    // Define uma caneta padrão (preta, 2 pixels de largura) para os desenhos
    QPen caneta;
    caneta.setColor(Qt::black);
    caneta.setWidth(2);
    painter.setPen(caneta);

    // 1. Percorre a lista de todos os objetos virtuais
    for (const ObjetoVirtual &objeto : *displayFile_ptr) {

        // Define a cor da caneta com base na cor guardada no objeto
        caneta.setColor(objeto.cor);
        painter.setPen(caneta); // Aplica a caneta (com a cor certa) ao pintor

        // 2. Verifica o tipo de cada objeto para saber como desenhá-lo
        switch (objeto.tipo) {

        case TipoObjeto::Ponto: {
            // Apenas desenha se a lista de pontos não estiver vazia
            if (!objeto.pontos.isEmpty()) {
                //pegando o primeiro ponto
                PontoMatriz ponto = objeto.pontos.first();
                //criando um QPointF pelo ponto e desenhando
                painter.drawPoint(QPointF(ponto.x(), ponto.y()));
            }
            break;
        }

        case TipoObjeto::Reta: {
            // Apenas desenha se tivermos exatamente 2 pontos (início e fim)
            if (objeto.pontos.size() == 2) {
                PontoMatriz pontos[2] = {objeto.pontos[0], objeto.pontos[1]};
                painter.drawLine(QPointF(pontos[0].x(), pontos[0].y()), QPointF(pontos[1].x(), pontos[1].y()));
            }
            break;
        }

        case TipoObjeto::Poligono: {
            // Apenas desenha se tivermos 3 ou mais pontos
            if (objeto.pontos.size() >= 3) {

                // 1. Cria a lista temporária para os pontos convertidos
                QVector<QPointF> pontosParaPintar;

                // 2. Loop que enche a lista temporária
                for (const PontoMatriz &ponto : objeto.pontos) {
                    pontosParaPintar.append(QPointF(ponto.x(), ponto.y()));
                }

                // 3. Chama a função de desenho uma única vez com a lista completa
                painter.drawPolygon(pontosParaPintar);
            }
            break;
        }
        } // fim do switch
    } // fim do for
}
