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


    // --- Etapa 2: Construir a Matriz de Normalização (Mundo -> SCN) ---
    Matriz T = Matriz::criarMatrizTranslacao(-centroWindow.x(), -centroWindow.y());
    Matriz R = Matriz::criarMatrizRotacao(-anguloWindow);

    // --- CORREÇÃO DE DISTORÇÃO (Parte 1) ---
    // Para normalizar sem distorcer, precisamos de mapear a MAIOR dimensão da window
    // (seja largura ou altura) para o tamanho do SCN (que é 2, de -1 a 1).
    double maiorDimensaoWindow = std::max(larguraWindow, alturaWindow);
    double fatorEscalaNorm = 2.0 / maiorDimensaoWindow;
    Matriz S_norm = Matriz::criarMatrizEscala(fatorEscalaNorm, fatorEscalaNorm);
    // -----------------------------------------
    Matriz M_norm = S_norm * R * T;


    // --- Etapa 3: Construir a Matriz de Viewport (SCN -> Tela) ---
    double larguraViewport = this->width();
    double alturaViewport = this->height();
    Matriz T_vp = Matriz::criarMatrizTranslacao(larguraViewport / 2.0, alturaViewport / 2.0);

    // --- CORREÇÃO DE DISTORÇÃO (Parte 2) ---
    // Para mapear o SCN para a viewport sem distorcer, precisamos de mapear o SCN
    // para a MENOR dimensão da viewport.
    double menorDimensaoViewport = std::min(larguraViewport, alturaViewport);
    double fatorEscalaVp = menorDimensaoViewport / 2.0;
    Matriz S_vp = Matriz::criarMatrizEscala(fatorEscalaVp, -fatorEscalaVp); // Inverte Y
    // -----------------------------------------
    Matriz M_vp = T_vp * S_vp;


    // --- Etapa Final: Retornar a Matriz Composta Total ---
    return M_vp * M_norm;
}

void TelaDeDesenho::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Deixa o desenho mais suave

    // --- Verificações de Segurança ---
    // Só desenha se tivermos um displayFile para usar
    if (!displayFile_ptr) {
        return;
    }

    // --- Etapa 1: Calcular a Matriz de Transformação ---
    // Esta matriz contém toda a lógica da câmera (Window/Viewport/SCN)
    Matriz M_wv = calcularMatrizDeVisualizacao();

    // --- Etapa 2: Desenhar todos os Objetos do Mundo ---

    // Define uma caneta padrão para garantir que os objetos sejam visíveis
    QPen canetaPadrao;
    canetaPadrao.setColor(Qt::white);
    canetaPadrao.setWidth(5); // Uma espessura visível

    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
        // Cria uma lista temporária para guardar os pontos já em coordenadas de tela
        QVector<QPointF> pontos_transformados;

        // Para cada ponto original do objeto no "mundo"...
        for (const Ponto &ponto_original : objeto.pontos) {
            // ...aplica a nossa matriz de visualização para encontrar sua posição na tela.
            Matriz ponto_na_tela_matriz = M_wv * ponto_original;

            // Converte o resultado para um QPointF que o QPainter entende
            pontos_transformados.append(QPointF(ponto_na_tela_matriz.getDados()[0][0],
                                                ponto_na_tela_matriz.getDados()[1][0]));
        }

        // Se o objeto não tiver pontos transformados, pula para o próximo
        if (pontos_transformados.isEmpty()) {
            continue;
        }

        // Define a cor da caneta para este objeto específico
        canetaPadrao.setColor(objeto.cor);
        painter.setPen(canetaPadrao);

        // Usa a lista 'pontos_transformados' para desenhar o objeto correto
        switch (objeto.tipo) {
        case TipoObjeto::Ponto: {
            painter.drawPoint(pontos_transformados.first());
            break;
        }

        case TipoObjeto::Reta: {
            if (pontos_transformados.size() == 2) {
                painter.drawLine(pontos_transformados[0], pontos_transformados[1]);
            }
            break;
        }

        case TipoObjeto::Poligono: {
            // drawPolygon funciona para polígonos com 3 ou mais vértices
            if (pontos_transformados.size() >= 3) {
                painter.drawPolygon(pontos_transformados);
            }
            break;
        }
        } // Fim do switch
    } // Fim do loop for
}
