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

// Função que calcula o código de região de 4 bits para um ponto no SCN
int TelaDeDesenho::calcularOutcode(const Ponto &p) const {
    int code = DENTRO;
    if (p.x() < -1.0) code |= ESQUERDA;
    else if (p.x() > 1.0) code |= DIREITA;
    if (p.y() < -1.0) code |= ABAIXO;
    else if (p.y() > 1.0) code |= ACIMA;
    return code;
}

// Implementação do algoritmo de recorte de Cohen-Sutherland
bool TelaDeDesenho::clipCohenSutherland(Ponto &p1, Ponto &p2) const {
    int outcode1 = calcularOutcode(p1);
    int outcode2 = calcularOutcode(p2);

    while (true) {
        if (!(outcode1 | outcode2)) { // Aceitação trivial: ambos dentro
            return true;
        } else if (outcode1 & outcode2) { // Rejeição trivial: ambos na mesma região "fora"
            return false;
        } else { // Candidata a recorte
            double x, y;
            int outcodeFora = outcode2 > outcode1 ? outcode2 : outcode1;

            // Encontra o ponto de interseção com a borda do SCN
            if (outcodeFora & ACIMA) {
                x = p1.x() + (p2.x() - p1.x()) * (1.0 - p1.y()) / (p2.y() - p1.y());
                y = 1.0;
            } else if (outcodeFora & ABAIXO) {
                x = p1.x() + (p2.x() - p1.x()) * (-1.0 - p1.y()) / (p2.y() - p1.y());
                y = -1.0;
            } else if (outcodeFora & DIREITA) {
                y = p1.y() + (p2.y() - p1.y()) * (1.0 - p1.x()) / (p2.x() - p1.x());
                x = 1.0;
            } else { // ESQUERDA
                y = p1.y() + (p2.y() - p1.y()) * (-1.0 - p1.x()) / (p2.x() - p1.x());
                x = -1.0;
            }

            // Atualiza o ponto que estava fora com a nova interseção
            if (outcodeFora == outcode1) {
                p1 = Ponto(x, y);
                outcode1 = calcularOutcode(p1);
            } else {
                p2 = Ponto(x, y);
                outcode2 = calcularOutcode(p2);
            }
        }
    }
}

void TelaDeDesenho::calcularMatrizDeVisualizacao(Matriz& m_norm, Matriz& m_vp) const
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

    if (!encontrouWindow) { // Se não achar, retorna matrizes identidade
        m_norm = Matriz::criarIdentidade();
        m_vp = Matriz::criarIdentidade();
        return;
    }

    Ponto centroWindow = windowObj.calcularCentro();
    Ponto p0 = windowObj.pontos[0], p1 = windowObj.pontos[1], p3 = windowObj.pontos[3];
    double dx_largura = p1.x() - p0.x(), dy_largura = p1.y() - p0.y();
    double larguraWindow = std::sqrt(dx_largura * dx_largura + dy_largura * dy_largura);
    double dx_altura = p3.x() - p0.x(), dy_altura = p3.y() - p0.y();
    double alturaWindow = std::sqrt(dx_altura * dx_altura + dy_altura * dy_altura);
    double anguloRadianos = std::atan2(dy_largura, dx_largura);
    double anguloWindow = anguloRadianos * 180.0 / M_PI;

    if (larguraWindow < 1e-6 || alturaWindow < 1e-6) { // Proteção
        m_norm = Matriz::criarIdentidade();
        m_vp = Matriz::criarIdentidade();
        return;
    }

    // --- Etapa 2: Corrigir a Proporção (Aspect Ratio) ---
    // Pega as dimensões da sua viewport final
    double margem = 20.0; // Usando o valor que você definiu no paintEvent
    double vp_largura = this->width() - 2 * margem;
    double vp_altura = this->height() - 3 * margem; // Usando sua margem assimétrica
    if (vp_largura < 1 || vp_altura < 1) { /* retorna matrizes identidade */ }

    double ar_viewport = vp_largura / vp_altura;
    double ar_window = larguraWindow / alturaWindow;

    double larguraWindowCorrigida = larguraWindow;
    double alturaWindowCorrigida = alturaWindow;

    // Compara as proporções. O objetivo é criar uma "área de visão" no mundo
    // que tenha a mesma proporção da viewport, para evitar distorção.
    if (ar_window > ar_viewport) {
        // A Window é mais "larga" que a Viewport. A altura da Window será aumentada
        // para corresponder à proporção, mostrando mais coisas acima e abaixo (letterboxing).
        alturaWindowCorrigida = larguraWindow / ar_viewport;
    } else {
        // A Window é mais "alta" que a Viewport. A largura da Window será aumentada
        // para corresponder, mostrando mais coisas nos lados (pillarboxing).
        larguraWindowCorrigida = alturaWindow * ar_viewport;
    }

    // --- Etapa 3: Construir a Matriz de Normalização (Mundo -> SCN) ---
    // Agora usamos as dimensões CORRIGIDAS para garantir que não haja distorção.
    Matriz T = Matriz::criarMatrizTranslacao(-centroWindow.x(), -centroWindow.y());
    Matriz R = Matriz::criarMatrizRotacao(-anguloWindow);
    Matriz S_norm = Matriz::criarMatrizEscala(2.0 / larguraWindowCorrigida, 2.0 / alturaWindowCorrigida);
    m_norm = S_norm * R * T;

    // --- Etapa 4: Construir a Matriz de Viewport (SCN -> Tela) ---
    // Esta matriz agora simplesmente mapeia o SCN para a viewport retangular.
    double vp_x_min = margem;
    double vp_y_min = margem * 2;
    Matriz S_vp = Matriz::criarMatrizEscala(vp_largura / 2.0, -vp_altura / 2.0);
    Matriz T_vp = Matriz::criarMatrizTranslacao(vp_x_min + vp_largura / 2.0, vp_y_min + vp_altura / 2.0);
    m_vp = T_vp * S_vp;
}

void TelaDeDesenho::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. Prepara a tela
    painter.fillRect(this->rect(), Qt::black);

    if (!displayFile_ptr || displayFile_ptr->isEmpty()) return;

    // 2. Obtém as matrizes de transformação separadas
    Matriz M_norm, M_vp;
    calcularMatrizDeVisualizacao(M_norm, M_vp);

    // 3. Desenha os objetos, aplicando a pipeline de recorte
    QPen canetaPadrao;
    canetaPadrao.setWidth(2);

    for (const ObjetoVirtual &objeto : *displayFile_ptr) {
        if (objeto.nome == "#WINDOW_CAMERA") continue;

        canetaPadrao.setColor(objeto.cor);
        painter.setPen(canetaPadrao);
        painter.setBrush(Qt::NoBrush);

        if (objeto.tipo == TipoObjeto::Ponto) {
            if (objeto.pontos.isEmpty()) continue;
            Ponto p_scn = Ponto(M_norm * objeto.pontos.first());
            // Recorte de Ponto: só desenha se estiver dentro do SCN
            if (p_scn.x() >= -1 && p_scn.x() <= 1 && p_scn.y() >= -1 && p_scn.y() <= 1) {
                Ponto p_vp = Ponto(M_vp * p_scn);
                painter.drawPoint(QPointF(p_vp.x(), p_vp.y()));
            }
        } else { // Retas e Polígonos são tratados como segmentos de reta
            for (int i = 0; i < objeto.pontos.size(); ++i) {
                Ponto p1_mundo = objeto.pontos[i];
                Ponto p2_mundo = (objeto.tipo == TipoObjeto::Reta)
                                     ? objeto.pontos[i+1]
                                     : objeto.pontos[(i + 1) % objeto.pontos.size()];

                Ponto p1_scn = Ponto(M_norm * p1_mundo);
                Ponto p2_scn = Ponto(M_norm * p2_mundo);

                // Aplica o recorte na reta em SCN
                if (clipCohenSutherland(p1_scn, p2_scn)) {
                    // Se a reta sobreviveu, transforma para a viewport e desenha
                    Ponto p1_vp = Ponto(M_vp * p1_scn);
                    Ponto p2_vp = Ponto(M_vp * p2_scn);
                    painter.drawLine(QPointF(p1_vp.x(), p1_vp.y()), QPointF(p2_vp.x(), p2_vp.y()));
                }
                if (objeto.tipo == TipoObjeto::Reta) break;
            }
        }
    }

    // 4. Desenha a borda da viewport por último, usando sua lógica de margem
    double margem = 20.0;
    QRectF viewportRect(margem, margem * 2 , this->width() - 2 * margem, this->height() - 3 * margem);
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawRect(viewportRect);
}
