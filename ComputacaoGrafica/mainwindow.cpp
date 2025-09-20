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
    windowObj.cor = Qt::gray; // Uma cor para podermos vê-la
    // Criamos um retângulo padrão de 200x200 centrado na origem
    windowObj.pontos.append(Ponto(-100, -100));
    windowObj.pontos.append(Ponto(100, -100));
    windowObj.pontos.append(Ponto(100, 100));
    windowObj.pontos.append(Ponto(-100, 100));
    displayFile.append(windowObj);
    indiceDaWindow = displayFile.size() - 1; // Guardamos o índice dela

    // --- Exemplo de criação de objetos ---
    //declaração de coordenadas, uma lista de pontos que um desenho tem. vai servir para atribuir a matriz em PontoMatriz
    QVector<Ponto> coordenadas;

    // 1. Criar uma casa
    ObjetoVirtual casa;
    casa.nome = "Casa";
    casa.tipo = TipoObjeto::Poligono;
    coordenadas = {Ponto(-80, 40), // Base inferior esquerda
        Ponto(-40, 40), // Base inferior direita
        Ponto(-40, 70), // Canto superior direito da parede
        Ponto(-60, 90), // Pico do telhado
        Ponto(-80, 70)  // Canto superior esquerdo da parede
    };

    //adicionando em pontos cada matriz de coordenada
    for(const Ponto &ponto : coordenadas) {
        casa.pontos.append(ponto);
    }
    casa.cor = Qt::green;

    coordenadas.clear();

    //2. Criar um coração
    ObjetoVirtual coxinha;
    coxinha.nome = "Coxinha";
    coxinha.tipo = TipoObjeto::Poligono;
    coordenadas = {Ponto(0, -50),   Ponto(3, -52),   Ponto(6, -54),   Ponto(9, -56),
                   Ponto(12, -58),  Ponto(15, -60),  Ponto(18, -62),  Ponto(21, -64),
                   Ponto(23, -66),  Ponto(25, -69),  Ponto(27, -72),  Ponto(28, -75),
                   Ponto(29, -78),  Ponto(29, -82),  Ponto(28, -85),  Ponto(26, -88),
                   Ponto(24, -91),  Ponto(21, -93),  Ponto(17, -95),  Ponto(13, -97),
                   Ponto(9, -98),   Ponto(4, -99),   Ponto(0, -99),   Ponto(-4, -99),
                   Ponto(-9, -98),  Ponto(-13, -97), Ponto(-17, -95), Ponto(-21, -93),
                   Ponto(-24, -91), Ponto(-26, -88), Ponto(-28, -85), Ponto(-29, -82),
                   Ponto(-29, -78), Ponto(-28, -75), Ponto(-27, -72), Ponto(-25, -69),
                   Ponto(-23, -66), Ponto(-21, -64), Ponto(-18, -62), Ponto(-15, -60),
                   Ponto(-12, -58), Ponto(-9, -56),  Ponto(-6, -54),  Ponto(-3, -52)
    };

    //adicionando em pontos cada matriz de coordenada
    for(const Ponto &ponto : coordenadas) {
        coxinha.pontos.append(ponto);
    }
    coxinha.cor = Qt::red;
    coordenadas.clear();

    //Criar um círculo
    ObjetoVirtual circulo;
    circulo.nome = "Círculo";
    circulo.tipo = TipoObjeto::Poligono;
    coordenadas = {Ponto(75, 75),   Ponto(74, 82),   Ponto(71, 88),   Ponto(66, 93),
                   Ponto(60, 97),   Ponto(53, 99),   Ponto(45, 100),  Ponto(38, 99),
                   Ponto(31, 97),   Ponto(25, 93),   Ponto(20, 88),   Ponto(17, 82),
                   Ponto(15, 75),   Ponto(17, 68),   Ponto(20, 62),   Ponto(25, 57),
                   Ponto(31, 53),   Ponto(38, 51),   Ponto(45, 50),   Ponto(53, 51),
                   Ponto(60, 53),   Ponto(66, 57),   Ponto(71, 62),   Ponto(74, 68)
    };

    //adicionando em pontos cada matriz de coordenada
    for(const Ponto &ponto : coordenadas) {
        circulo.pontos.append(ponto);
    }
    circulo.cor = Qt::yellow;

    coordenadas.clear();

    // 5. Adicionar os objetos ao Display File
    displayFile.append(casa);
    displayFile.append(coxinha);
    displayFile.append(circulo);


    ui->TelaDesenho->setDisplayFile(&displayFile);

    // --- Ajuste Inicial ---
    ajustarWindowParaCena();

    // ---- DEBUG: VERIFICAR ESTADO INICIAL DA WINDOW ----
    printf("\n--- Estado da Window APÓS a criação ---\n");
    displayFile[indiceDaWindow].imprimir(); // Vamos criar um método imprimir no ObjetoVirtual
    // --------------------------------------------------



    //Percorrendo o displayFile para adicionar os objetos no combobox (seleção de objetos a serem alterados)
    for (int i = 0; i < displayFile.size(); i++) {
        ui->objectSelectorComboBox->addItem(displayFile[i].nome);
    }

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
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.transladar(0, -10); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
}


void MainWindow::on_panRightButton_clicked()
{
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.transladar(10, 0); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
}




void MainWindow::on_panDownButton_clicked()
{
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.transladar(0, 10); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
}


void MainWindow::on_panLeftButton_clicked()
{
    // Pega o nosso objeto Window pelo índice que guardámos
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    // Aplica a translação diretamente no objeto
    windowObj.transladar(-10, 0); // Move a "câmera" para cima

    ui->TelaDesenho->update(); // Manda redesenhar com a câmera na nova posição
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

