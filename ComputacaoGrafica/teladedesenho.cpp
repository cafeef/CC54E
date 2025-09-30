#include "teladedesenho.h"
#include <QPainter> // A classe QPainter é a "caneta" que usamos para desenhar
#include <cmath>
#include <algorithm>

TelaDeDesenho::TelaDeDesenho(QWidget *parent) : QWidget(parent)
{
    // Define um fundo preto para a nossa área de desenho
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    setPalette(pal);
}

void TelaDeDesenho::setDisplayFile(QVector<ObjetoVirtual> *df_ptr) {
    this->displayFile_ptr = df_ptr; // Guarda o ponteiro
}

Matriz TelaDeDesenho::calcularMatrizDeVisualizacao() const
{
    // --- Etapa 1: Encontrar e Extrair Dados do Objeto Window ---
    ObjetoVirtual windowObj;
    bool encontrouWindow = false;
    for (const auto &obj : *displayFile_ptr) {
        if (obj.nome == "#WINDOW_CAMERA") {
            windowObj = obj;
            encontrouWindow = true;
            break;
        }
    }
    if (!encontrouWindow) return Matriz::criarIdentidade();

    Ponto centroWindow = windowObj.calcularCentro();
    Ponto p0 = windowObj.pontos[0], p1 = windowObj.pontos[1], p3 = windowObj.pontos[3];
    double dx_largura = p1.x() - p0.x(), dy_largura = p1.y() - p0.y();
    double larguraWindow = std::sqrt(dx_largura * dx_largura + dy_largura * dy_largura);
    double dx_altura = p3.x() - p0.x(), dy_altura = p3.y() - p0.y();
    double alturaWindow = std::sqrt(dx_altura * dx_altura + dy_altura * dy_altura);
    double anguloRadianos = std::atan2(dy_largura, dx_largura);
    double anguloWindow = anguloRadianos * 180.0 / M_PI;

    // Proteção contra window com tamanho zero
    if (larguraWindow < 1e-6 || alturaWindow < 1e-6) return Matriz::criarIdentidade();

    // --- Etapa 2: Definir a Viewport Interna ---
    double margem = 15.0;
    double vp_x_min = margem;
    double vp_y_min = margem;
    double vp_largura = this->width() - 2 * margem;
    double vp_altura = this->height() - 2 * margem;

    // --- Etapa 3: Calcular o Fator de Escala Uniforme (A Correção Definitiva) ---
    double fatorEscalaX = vp_largura / larguraWindow;
    double fatorEscalaY = vp_altura / alturaWindow;

    // Usa o MENOR dos dois fatores para garantir que tudo caiba sem distorcer
    double fatorEscalaUniforme = std::min(fatorEscalaX, fatorEscalaY);

    // --- Etapa 4: Construir a Matriz Final Composta ---
    Matriz T_mundo = Matriz::criarMatrizTranslacao(-centroWindow.x(), -centroWindow.y());
    Matriz R = Matriz::criarMatrizRotacao(-anguloWindow);
    Matriz S = Matriz::criarMatrizEscala(fatorEscalaUniforme, -fatorEscalaUniforme); // Escala uniforme e inverte Y
    Matriz T_vp = Matriz::criarMatrizTranslacao(vp_x_min + vp_largura / 2.0, vp_y_min + vp_altura / 2.0);

    // A ordem da composição é crucial: primeiro mundo, depois viewport
    return T_vp * S * R * T_mundo;
}

void TelaDeDesenho::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Limpa a tela
    painter.fillRect(this->rect(), Qt::black);

    // --- Etapa 1: Obter a Matriz de Transformação Final ---
    Matriz M_final = calcularMatrizDeVisualizacao();

    // --- Etapa 2: Desenhar os Objetos (SEM CLIPPING POR AGORA) ---
    QPen canetaPadrao;
    canetaPadrao.setWidth(2);

    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
        if (objeto.nome == "#WINDOW_CAMERA") continue;

        canetaPadrao.setColor(objeto.cor);
        painter.setPen(canetaPadrao);

        // Transforma todos os pontos do objeto de uma vez
        QVector<QPointF> pontos_na_tela;
        for (const Ponto &p_mundo : objeto.pontos) {
            Ponto p_tela = Ponto(M_final * p_mundo);
            pontos_na_tela.append(QPointF(p_tela.x(), p_tela.y()));
        }

        if (pontos_na_tela.isEmpty()) continue;

        // Desenha a forma usando os pontos já na tela
        if (objeto.tipo == TipoObjeto::Ponto) {
            painter.drawPoint(pontos_na_tela.first());
        } else if (objeto.tipo == TipoObjeto::Reta) {
            if (pontos_na_tela.size() == 2) painter.drawLine(pontos_na_tela[0], pontos_na_tela[1]);
        } else if (objeto.tipo == TipoObjeto::Poligono) {
            painter.drawPolygon(pontos_na_tela);
        }
    }

    // --- 4. DESENHAR A INTERFACE (A BORDA DA VIEWPORT) ---
    // Esta é a última coisa a ser desenhada, garantindo que fique por cima de tudo.
    double margem = 15.0;
    QRectF viewportRect(margem, margem, this->width() - 2 * margem, this->height() - 2 * margem);

    // Usa uma cor contrastante com o fundo preto
    painter.setPen(QPen(Qt::gray, 1)); // Caneta cinza de 1 pixel
    painter.setBrush(Qt::NoBrush); // Garante que o retângulo não tenha preenchimento
    painter.drawRect(viewportRect);
}
