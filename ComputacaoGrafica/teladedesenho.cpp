#include "teladedesenho.h"
#include <QPainter> // A classe QPainter é a "caneta" que usamos para desenhar

TelaDeDesenho::TelaDeDesenho(QWidget *parent) : QWidget(parent)
{
    // Define um fundo branco para a nossa área de desenho
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setPalette(pal);
}

void TelaDeDesenho::setDisplayFile(const QVector<ObjetoVirtual> &df)
{
    this->displayFile = df; // Copia a lista de objetos recebida
    update(); // Força o widget a redesenhar-se, chamando o paintEvent()
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
    for (const ObjetoVirtual &objeto : displayFile) {

        // 2. Verifica o tipo de cada objeto para saber como desenhá-lo
        switch (objeto.tipo) {

        case TipoObjeto::Ponto: {
            // Apenas desenha se a lista de pontos não estiver vazia
            if (!objeto.pontos.isEmpty()) {
                painter.drawPoint(objeto.pontos.first());
            }
            break;
        }

        case TipoObjeto::Reta: {
            // Apenas desenha se tivermos exatamente 2 pontos (início e fim)
            if (objeto.pontos.size() == 2) {
                painter.drawLine(objeto.pontos[0], objeto.pontos[1]);
            }
            break;
        }

        case TipoObjeto::Poligono: {
            // Apenas desenha se tivermos 3 ou mais pontos para formar um polígono
            // O QPainter.drawPolygon já sabe como conectar os pontos!
            if (objeto.pontos.size() >= 3) {
                painter.drawPolygon(objeto.pontos);
            }
            break;
        }
        } // fim do switch
    } // fim do for
}
