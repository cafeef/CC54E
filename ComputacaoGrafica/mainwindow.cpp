#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "estruturas.h"
#include <cmath>
#include <limits>
#include <vector> // Para std::vector
#include <QString>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- Criação da Window como um Objeto ---
    ObjetoVirtual windowObj;
    windowObj.nome = "#WINDOW_CAMERA"; // Um nome especial para a identificarmos
    windowObj.tipo = TipoObjeto::Poligono;
    // Criamos um retângulo padrão de 200x200 centrado na origem
    windowObj.pontos.append(Ponto(-100, -100));
    windowObj.pontos.append(Ponto(100, -100));
    windowObj.pontos.append(Ponto(100, 100));
    windowObj.pontos.append(Ponto(-100, 100));
    displayFile.append(windowObj);
    indiceDaWindow = displayFile.size() - 1; // Guardamos o índice dela

    // --- Exemplo de criação de objetos ---
    //declaração de coordenadas, uma lista de pontos que um desenho tem. vai servir para atribuir a matriz em PontoMatriz
    // Cria uma casa completa na posição (200, 200)
    QVector<ObjetoVirtual> casa = criarCasaCompleta(200, 200, "Casa de Campo");
    displayFile.append(casa);

    // Cria uma flor na posição (-150, 100)
    QVector<ObjetoVirtual> flor = criarFlor(-150, 100, "Girassol");
    displayFile.append(flor);

    // Cria um Pikachu na posição (0, -200)
    QVector<ObjetoVirtual> pikachu = criarPikachu(0, -200, "Pikachu");
    displayFile.append(pikachu);


    ui->TelaDesenho->setDisplayFile(&displayFile);

    // --- Ajuste Inicial ---
    ajustarWindowParaCena();


    //Percorrendo o displayFile para adicionar os objetos no combobox (seleção de objetos a serem alterados)
    for (int i = 0; i < displayFile.size(); i++) {
        ui->objectSelectorComboBox->addItem(displayFile[i].nome);
    }

}

QVector<ObjetoVirtual> MainWindow::criarCasaCompleta(double x_centro, double y_centro, const QString& nome_base) {
    QVector<ObjetoVirtual> partesDaCasa;

    // --- Parte 1: Estrutura da Casa (Paredes e Telhado) ---
    ObjetoVirtual estrutura;
    estrutura.nome = nome_base;
    estrutura.tipo = TipoObjeto::Poligono;
    estrutura.cor = QColor("#D2B48C"); // Cor Tan (madeira clara)

    // Coordenadas locais da estrutura (em torno de 0,0)
    QVector<Ponto> coordsEstrutura = {
        Ponto(-50, -40), Ponto(50, -40), Ponto(50, 40), Ponto(0, 70), Ponto(-50, 40)
    };
    for (const auto& p : coordsEstrutura) {
        // Adiciona o deslocamento para a posição final
        estrutura.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesDaCasa.append(estrutura);

    // --- Parte 2: A Porta ---
    ObjetoVirtual porta;
    porta.nome = nome_base + " - Porta";
    porta.tipo = TipoObjeto::Poligono;
    porta.cor = QColor("#8B4513"); // Cor SaddleBrown (madeira escura)

    // Coordenadas locais da porta
    QVector<Ponto> coordsPorta = {
        Ponto(-10, -40), Ponto(10, -40), Ponto(10, 0), Ponto(-10, 0)
    };
    for (const auto& p : coordsPorta) {
        porta.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesDaCasa.append(porta);

    return partesDaCasa;
}


QVector<ObjetoVirtual> MainWindow::criarFlor(double x_centro, double y_centro, const QString& nome_base) {
    QVector<ObjetoVirtual> partesDaFlor;

    // --- Parte 1: O Miolo (Centro) ---
    ObjetoVirtual miolo;
    miolo.nome = nome_base + " - Miolo";
    miolo.tipo = TipoObjeto::Poligono;
    miolo.cor = Qt::yellow;

    // Cria um polígono que aproxima um círculo para o miolo
    for (int i = 0; i < 12; ++i) {
        double angulo = i * (360.0 / 12.0) * M_PI / 180.0; // Ângulo em radianos
        double raio = 15.0;
        miolo.pontos.append(Ponto(raio * cos(angulo) + x_centro, raio * sin(angulo) + y_centro));
    }
    partesDaFlor.append(miolo);

    // --- Parte 2: As Pétalas ---
    // Coordenadas de uma pétala "mestra"
    QVector<Ponto> coordsPetalaMestra = {
        Ponto(0, 0), Ponto(-15, 30), Ponto(0, 50), Ponto(15, 30)
};

// Cria 6 pétalas, rotacionando a pétala mestra
for (int i = 0; i < 6; ++i) {
    ObjetoVirtual petala;
    petala.nome = QString(nome_base + " - Pétala %1").arg(i + 1);
    petala.tipo = TipoObjeto::Poligono;
    petala.cor = Qt::red;

    double anguloRotacao = i * 60.0; // Rotaciona cada pétala em 60 graus

    // Cria a matriz de rotação para esta pétala
    Matriz R = Matriz::criarMatrizRotacao(anguloRotacao);

    for (const auto& p_mestra : coordsPetalaMestra) {
        Ponto p_rotacionada = Ponto(R * p_mestra);
        petala.pontos.append(Ponto(p_rotacionada.x() + x_centro, p_rotacionada.y() + y_centro));
    }
    partesDaFlor.append(petala);
}

return partesDaFlor;
}

QVector<ObjetoVirtual> MainWindow::criarPikachu(double x_centro, double y_centro, const QString& nome_base) {
    QVector<ObjetoVirtual> partesPikachu;
    double escala = 1.5; // Fator de escala para ajustar o tamanho do desenho

    // --- Parte 1: Corpo (Polígono principal) ---
    ObjetoVirtual corpo;
    corpo.nome = nome_base + " - Corpo";
    corpo.tipo = TipoObjeto::Poligono;
    corpo.cor = QColor("#FFDE00"); // Amarelo Pikachu

    QVector<Ponto> coordsCorpo = {
        Ponto(0,-60), Ponto(-25,-58), Ponto(-45,-50), Ponto(-60,-35), Ponto(-70,-15),
        Ponto(-75,10), Ponto(-70,30), Ponto(-55,50), Ponto(-35,65), Ponto(-20,70),
        Ponto(0,72), Ponto(20,70), Ponto(35,65), Ponto(55,50), Ponto(70,30),
        Ponto(75,10), Ponto(70,-15), Ponto(60,-35), Ponto(45,-50), Ponto(25,-58)
    };
    for (const auto& p : coordsCorpo) {
        corpo.pontos.append(Ponto(p.x() * escala + x_centro, p.y() * escala + y_centro));
    }
    partesPikachu.append(corpo);

    // --- Parte 2: Orelhas ---
    ObjetoVirtual orelhaEsq, orelhaDir;
    orelhaEsq.nome = nome_base + " - Orelha Esq"; orelhaDir.nome = nome_base + " - Orelha Dir";
    orelhaEsq.tipo = orelhaDir.tipo = TipoObjeto::Poligono;
    orelhaEsq.cor = orelhaDir.cor = Qt::black;

    QVector<Ponto> coordsOrelha = { Ponto(-35,65), Ponto(-45,100), Ponto(-30,95) };
    for (const auto& p : coordsOrelha) {
        orelhaEsq.pontos.append(Ponto(p.x() * escala + x_centro, p.y() * escala + y_centro));
        orelhaDir.pontos.append(Ponto(-p.x() * escala + x_centro, p.y() * escala + y_centro)); // Espelha para a direita
    }
    partesPikachu.append(orelhaEsq);
    partesPikachu.append(orelhaDir);

    // --- Parte 3: Bochechas ---
    ObjetoVirtual bochechaEsq, bochechaDir;
    bochechaEsq.nome = nome_base + " - Bochecha Esq"; bochechaDir.nome = nome_base + " - Bochecha Dir";
    bochechaEsq.tipo = bochechaDir.tipo = TipoObjeto::Poligono;
    bochechaEsq.cor = bochechaDir.cor = Qt::red;

    for(int i = 0; i < 8; ++i) {
        double angulo = i * (360.0/8.0) * M_PI / 180.0;
        double raio = 10.0 * escala;
        double centroBochechaX = 50.0 * escala;
        double centroBochechaY = 15.0 * escala;
        bochechaEsq.pontos.append(Ponto(raio*cos(angulo) - centroBochechaX + x_centro, raio*sin(angulo) + centroBochechaY + y_centro));
        bochechaDir.pontos.append(Ponto(raio*cos(angulo) + centroBochechaX + x_centro, raio*sin(angulo) + centroBochechaY + y_centro));
    }
    partesPikachu.append(bochechaEsq);
    partesPikachu.append(bochechaDir);

    // --- Parte 4: Rabo ---
    ObjetoVirtual rabo;
    rabo.nome = nome_base + " - Rabo";
    rabo.tipo = TipoObjeto::Poligono;
    rabo.cor = QColor("#FFDE00");

    QVector<Ponto> coordsRabo = {
        Ponto(-70,-15), Ponto(-90,-30), Ponto(-80,-40), Ponto(-110,-55),
        Ponto(-100,-65), Ponto(-130,-80), Ponto(-120,-90), Ponto(-110,-80),
        Ponto(-80,-65), Ponto(-90,-55), Ponto(-60,-40), Ponto(-70,-25)
    };
    for (const auto& p : coordsRabo) {
        rabo.pontos.append(Ponto(p.x() * escala + x_centro, p.y() * escala + y_centro));
    }
    partesPikachu.append(rabo);

    return partesPikachu;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ajustarWindowParaCena()
{
    // Pega uma referência ao nosso objeto window para o modificarmos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Cria uma lista temporária com todos os pontos de TODOS os objetos,
    // exceto os da própria window.
    std::vector<Ponto> todosOsPontos;
    for (int i = 0; i < displayFile.size(); ++i) {
        if (i == indiceDaWindow) continue; // Pula o objeto window
        for (const Ponto &ponto : displayFile[i].pontos) {
            todosOsPontos.push_back(ponto);
        }
    }

    // --- LÓGICA DE DECISÃO ---

    // Se a lista de pontos estiver vazia (não há outros objetos para enquadrar)...
    if (todosOsPontos.empty()) {
        // ...então redefinimos a window para o seu estado padrão.
        // Um retângulo de 200x200 centrado na origem.
        windowObj.pontos.clear();
        windowObj.pontos.append(Ponto(-100, -100));
        windowObj.pontos.append(Ponto(100, -100));
        windowObj.pontos.append(Ponto(100, 100));
        windowObj.pontos.append(Ponto(-100, 100));
        return; // E terminamos a função aqui.
    }

    // --- Se chegamos aqui, significa que HÁ objetos para enquadrar ---

    // Encontra os limites da cena (Bounding Box) usando a lista que criámos
    double minX = todosOsPontos[0].x();
    double minY = todosOsPontos[0].y();
    double maxX = todosOsPontos[0].x();
    double maxY = todosOsPontos[0].y();

    for (const Ponto &ponto : todosOsPontos) {
        if (ponto.x() < minX) minX = ponto.x();
        if (ponto.x() > maxX) maxX = ponto.x();
        if (ponto.y() < minY) minY = ponto.y();
        if (ponto.y() > maxY) maxY = ponto.y();
    }

    // Calcula o novo centro e tamanho com uma margem de 10%
    double centroX = (minX + maxX) / 2.0;
    double centroY = (minY + maxY) / 2.0;
    double larguraCena = (maxX - minX) * 1.1;
    double alturaCena = (maxY - minY) * 1.1;

    // Garante que a window não tenha tamanho zero se a cena for um único ponto
    if (larguraCena < 1e-6) larguraCena = 10;
    if (alturaCena < 1e-6) alturaCena = 10;

    // Limpa os pontos antigos e define os novos que enquadram a cena
    windowObj.pontos.clear();
    windowObj.pontos.append(Ponto(centroX - larguraCena / 2, centroY - alturaCena / 2));
    windowObj.pontos.append(Ponto(centroX + larguraCena / 2, centroY - alturaCena / 2));
    windowObj.pontos.append(Ponto(centroX + larguraCena / 2, centroY + alturaCena / 2));
    windowObj.pontos.append(Ponto(centroX - larguraCena / 2, centroY + alturaCena / 2));
}

void MainWindow::on_translateButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    if (indiceSelecionado < 0) return; // Proteção para evitar crash

    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];

    // Alvos finais da translação
    double dx_final = ui->translateXSpinBox->value();
    double dy_final = ui->translateYSpinBox->value();

    // --- Nova Lógica de Animação ---

    const int duracao_ms = 1000; // Duração total da animação (1 segundo)
    const int intervalo_ms = 20; // Atualizar a cada 20ms (50 frames por segundo)
    int passos_totais = duracao_ms / intervalo_ms;

    // Calcula o pequeno passo a ser dado em cada intervalo para X e Y
    // Funciona para valores positivos e negativos!
    double passo_x = dx_final / passos_totais;
    double passo_y = dy_final / passos_totais;

    // Usamos um contador para saber quando parar
    int passos_dados = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=, &objetoSelecionado]() mutable {
        // Condição de parada: já demos todos os passos?
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            // Opcional: garantir que o objeto está na posição exata no final
            // (pode haver pequenos erros de arredondamento)
            // objetoSelecionado.transladar(dx_final - (passo_x * passos_dados), ...);
            return;
        }

        // APLICA O PASSO PEQUENO E CONSTANTE
        // O sinal negativo no passo_y é para corresponder à coordenada Y da tela (que cresce para baixo)
        objetoSelecionado.transladar(passo_x, -passo_y);

        // Atualiza o contador e a tela
        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}

void MainWindow::on_escaleButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    if (indiceSelecionado < 0) return;

    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double sx_final = ui->escaleXSpinBox->value();
    double sy_final = ui->escaleYSpinBox->value();

    // Configurações da animação
    const int duracao_ms = 1000; // 1 segundo
    const int intervalo_ms = 20;  // 50 FPS
    int passos_totais = duracao_ms / intervalo_ms;

    // Calcula o fator multiplicativo para cada passo.
    // Isso funciona para aumentar (sx > 1) e diminuir (sx < 1) a escala.
    double fator_x_passo = pow(sx_final, 1.0 / passos_totais);
    double fator_y_passo = pow(sy_final, 1.0 / passos_totais);

    int passos_dados = 0;
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=, &objetoSelecionado]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // Aplica o pequeno fator de escala incremental
        objetoSelecionado.escalonar(fator_x_passo, fator_y_passo);

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}

void MainWindow::on_rotationButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    if (indiceSelecionado < 0) return;

    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double anguloFinal = ui->rotationAngleSpinBox->value();

    // Configurações da animação
    const int duracao_ms = 1000; // 1 segundo
    const int intervalo_ms = 20;  // 50 FPS
    int passos_totais = duracao_ms / intervalo_ms;
    double passo_angulo = anguloFinal / passos_totais; // Funciona para ângulos positivos e negativos

    int passos_dados = 0;
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=, &objetoSelecionado]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // Aplica a pequena rotação incremental
        objetoSelecionado.rotacionar(passo_angulo);

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}


void MainWindow::on_escaleEixoButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    if (indiceSelecionado < 0) return;

    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double sx_final = ui->escaleXSpinBox->value();
    double sy_final = ui->escaleYSpinBox->value();

    // Configurações da animação
    const int duracao_ms = 1000; // 1 segundo
    const int intervalo_ms = 20;  // 50 FPS
    int passos_totais = duracao_ms / intervalo_ms;

    // Calcula o fator multiplicativo para cada passo
    double fator_x_passo = pow(sx_final, 1.0 / passos_totais);
    double fator_y_passo = pow(sy_final, 1.0 / passos_totais);

    int passos_dados = 0;
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=, &objetoSelecionado]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // Aplica o pequeno fator de escala incremental no eixo do objeto
        objetoSelecionado.escalonarEixo(fator_x_passo, fator_y_passo);

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}


void MainWindow::on_rotationEixoButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    if (indiceSelecionado < 0) return;

    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double anguloFinal = ui->rotationAngleSpinBox->value();

    // Configurações da animação
    const int duracao_ms = 1000; // 1 segundo
    const int intervalo_ms = 20;  // 50 FPS
    int passos_totais = duracao_ms / intervalo_ms;
    double passo_angulo = anguloFinal / passos_totais;

    int passos_dados = 0;
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [=, &objetoSelecionado]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // Aplica a pequena rotação incremental no eixo do objeto
        objetoSelecionado.rotacionarEixo(passo_angulo);

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}

void MainWindow::on_panUpButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double anguloGraus = windowObj.getAnguloEmGraus();
    double anguloRadianos = anguloGraus * M_PI / 180.0;
    double passo = 10.0; // O "para a frente" da câmera

    // A translação no mundo é baseada na rotação da câmera
    double dx = -passo * std::sin(anguloRadianos);
    double dy = passo * std::cos(anguloRadianos);

    windowObj.transladar(dx, dy);
    ui->TelaDesenho->update();
}

void MainWindow::on_panDownButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double anguloGraus = windowObj.getAnguloEmGraus();
    double anguloRadianos = anguloGraus * M_PI / 180.0;
    double passo = -10.0; // O "para trás" da câmera

    double dx = -passo * std::sin(anguloRadianos);
    double dy = passo * std::cos(anguloRadianos);

    windowObj.transladar(dx, dy);
    ui->TelaDesenho->update();
}

void MainWindow::on_panRightButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double anguloGraus = windowObj.getAnguloEmGraus();
    double anguloRadianos = anguloGraus * M_PI / 180.0;
    double passo = 10.0; // O "para a direita" da câmera

    // Para mover para a direita local, o vetor é (passo * cos, passo * sin)
    double dx = passo * std::cos(anguloRadianos);
    double dy = passo * std::sin(anguloRadianos);

    windowObj.transladar(dx, dy);
    ui->TelaDesenho->update();
}

void MainWindow::on_panLeftButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double anguloGraus = windowObj.getAnguloEmGraus();
    double anguloRadianos = anguloGraus * M_PI / 180.0;
    double passo = -10.0; // O "para a esquerda" da câmera

    double dx = passo * std::cos(anguloRadianos);
    double dy = passo * std::sin(anguloRadianos);

    windowObj.transladar(dx, dy);
    ui->TelaDesenho->update();
}


void MainWindow::on_zoomInButton_clicked()
{
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.escalonarEixo(0.9, 0.9); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
}


void MainWindow::on_zoomOutButton_clicked()
{
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.escalonarEixo(1.1, 1.1); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
}


void MainWindow::on_rotateRightButton_clicked()
{
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.rotacionarEixo(-5); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
}


void MainWindow::on_rotateLeftButton_clicked()
{
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.rotacionarEixo(5); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
}

