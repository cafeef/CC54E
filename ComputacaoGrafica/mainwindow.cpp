#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "estruturas.h"
#include <cmath>
#include <limits>
#include <vector> // Para std::vector
#include <QString>
#include <QTimer>
QVector<ObjetoVirtual> criarBolaPixar(double x_centro, double y_centro, const QString& nome_base);

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
    QVector<ObjetoVirtual> casa = criarCasaCompleta(300, 300, "Casa de Campo");
    displayFile.append(casa);

    // Cria uma flor na posição (-150, 100)
    QVector<ObjetoVirtual> flor = criarFlor(-150, 100, "Girassol");
    displayFile.append(flor);

    // Cria um Pikachu na posição (0, -200)
    QVector<ObjetoVirtual> pikachu = criarPikachu(0, -200, "Pikachu");
    displayFile.append(pikachu);

    QVector<ObjetoVirtual> bolaPixar = criarBolaPixar(250, 200, "Bola Pixar");
    displayFile.append(bolaPixar);

    QVector<ObjetoVirtual> cogumelo = criarCog(-500, -500, "Cogumelo");
    displayFile.append(cogumelo);


    ui->TelaDesenho->setDisplayFile(&displayFile);

    // --- Ajuste Inicial ---
    ajustarWindowParaCena();


    //Percorrendo o displayFile para adicionar os objetos no combobox (seleção de objetos a serem alterados)
  ui->objectSelectorComboBox->clear();

QStringList nomesAdicionados; // Lista para controlar nomes já adicionados

for (const ObjetoVirtual &objeto : displayFile) {
    QString nomeBase = objeto.nome.split(" - ").first(); // Pega a parte antes de " - "

    // Adiciona o nome base APENAS se ainda não estiver na lista
    if (!nomesAdicionados.contains(nomeBase)) {
        ui->objectSelectorComboBox->addItem(nomeBase);
        nomesAdicionados.append(nomeBase);
    }
}

}

QVector<ObjetoVirtual> MainWindow::criarCog(double x_centro, double y_centro, const QString& nome_base) {
    QVector<ObjetoVirtual> partesCogumelo;

    // --- Parte 1: Chapéu (Vermelho) ---
    ObjetoVirtual chapeu;
    chapeu.nome = nome_base + " - chapeu";
    chapeu.tipo = TipoObjeto::Poligono;
    chapeu.cor = Qt::red;

    QVector<Ponto> coordsChapeu = {
        Ponto(128, -64), Ponto(128, 32), Ponto(112, 32), Ponto(112, 48), Ponto(80, 80),
        Ponto(64, 96), Ponto(32, 128), Ponto(-32, 128), Ponto(-64, 96), Ponto(-80, 80),
        Ponto(-112, 48), Ponto(-112, 32), Ponto(-128, 32), Ponto(-128, -64)
    };
    for (const auto& p : coordsChapeu) {
        chapeu.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesCogumelo.append(chapeu);

    // --- Parte 2: Caule (Branco/Bege) ---
    ObjetoVirtual caule;
    caule.nome = nome_base + " - caule";
    caule.tipo = TipoObjeto::Poligono;
    caule.cor = QColor(255, 235, 205);

    QVector<Ponto> coordsCaule = {
        Ponto(0, -160), Ponto(48, -160), Ponto(48, -144), Ponto(80, -144), Ponto(80, -112),
        Ponto(112, -112), Ponto(112, -64), Ponto(-112, -64), Ponto(-112, -112), Ponto(-80, -112),
        Ponto(-80, -144), Ponto(-48, -144), Ponto(-48, -160), Ponto(0, -160)
    };
    for (const auto& p : coordsCaule) {
        caule.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesCogumelo.append(caule);

    // --- Parte 3: Olhos (Preto) ---
    ObjetoVirtual olhodir;
    olhodir.nome = nome_base + " - olho direito";
    olhodir.tipo = TipoObjeto::Poligono;
    olhodir.cor = Qt::black;

    QVector<Ponto> coordsOlhoDir = { Ponto(32, -80), Ponto(64, -80), Ponto(64, -112), Ponto(32, -112) };
    for (const auto& p : coordsOlhoDir) {
        olhodir.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesCogumelo.append(olhodir);

    ObjetoVirtual olhoesq;
    olhoesq.nome = nome_base + " - olho esquerdo";
    olhoesq.tipo = TipoObjeto::Poligono;
    olhoesq.cor = Qt::black;

    QVector<Ponto> coordsOlhoEsq = { Ponto(-64, -80), Ponto(-32, -80), Ponto(-32, -112), Ponto(-64, -112) };
    for (const auto& p : coordsOlhoEsq) {
        olhoesq.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesCogumelo.append(olhoesq);

    // --- Parte 4: Manchas (Branco) ---
    ObjetoVirtual manchasup;
    manchasup.nome = nome_base + " - Mancha superior";
    manchasup.tipo = TipoObjeto::Poligono;
    manchasup.cor = Qt::white;

    QVector<Ponto> coordsManchaSup = { Ponto(-32, 64), Ponto(32, 64), Ponto(32, 32), Ponto(-32, 32) };
    for (const auto& p : coordsManchaSup) {
        manchasup.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesCogumelo.append(manchasup);

    ObjetoVirtual manchaesq;
    manchaesq.nome = nome_base + " - mancha esquerda";
    manchaesq.tipo = TipoObjeto::Poligono;
    manchaesq.cor = Qt::white;

    QVector<Ponto> coordsManchaEsq = { Ponto(-80, 16), Ponto(-48, 16), Ponto(-48, -16), Ponto(-80, -16) };
    for (const auto& p : coordsManchaEsq) {
        manchaesq.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesCogumelo.append(manchaesq);

    ObjetoVirtual manchadir;
    manchadir.nome = nome_base + " - mancha direita";
    manchadir.tipo = TipoObjeto::Poligono;
    manchadir.cor = Qt::white;

    QVector<Ponto> coordsManchaDir = { Ponto(48, 16), Ponto(80, 16), Ponto(80, -16), Ponto(48, -16) };
    for (const auto& p : coordsManchaDir) {
        manchadir.pontos.append(Ponto(p.x() + x_centro, p.y() + y_centro));
    }
    partesCogumelo.append(manchadir);

    return partesCogumelo;
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
    orelhaEsq.cor = orelhaDir.cor = QColor("#FFDE00");

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
    // 1. Nome do objeto selecionado (ex: "Bola Pixar")
    QString nomeBaseSelecionado = ui->objectSelectorComboBox->currentText();
    if (nomeBaseSelecionado.isEmpty()) return;

    // 2. Pega o ângulo atual da câmera (window)
    double anguloCameraGraus = displayFile[indiceDaWindow].getAnguloEmGraus();
    double anguloCameraRad = anguloCameraGraus * M_PI / 180.0;

    // 3. Pega os valores desejados de translação (em pixels)
    double dx_final = ui->translateXSpinBox->value();
    double dy_final = ui->translateYSpinBox->value();

    // 4. Converte a translação para o eixo LOCAL da câmera
    double dx_corrigido = dx_final * cos(anguloCameraRad) - dy_final * sin(anguloCameraRad);
    double dy_corrigido = dx_final * sin(anguloCameraRad) + dy_final * cos(anguloCameraRad);

    // 5. Configura a animação
    const int duracao_ms = 1000;
    const int intervalo_ms = 20;
    int passos_totais = duracao_ms / intervalo_ms;
    double passo_x = dx_corrigido / passos_totais;
    double passo_y = dy_corrigido / passos_totais;
    int passos_dados = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // 6. Aplica a translação em todos os objetos que compartilham o mesmo prefixo
        for (ObjetoVirtual &objeto : displayFile) {
            if (objeto.nome.startsWith(nomeBaseSelecionado)) {
                objeto.transladar(passo_x, -passo_y); // "-passo_y" mantém o eixo Y da tela
            }
        }

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}

void MainWindow::on_escaleButton_clicked()
{
    // 1. Pega o NOME do objeto selecionado (ex: "Pikachu"), e não mais o índice.
    QString nomeBaseSelecionado = ui->objectSelectorComboBox->currentText();
    if (nomeBaseSelecionado.isEmpty() || nomeBaseSelecionado == "#WINDOW_CAMERA") return; // Proteção

    // Pega os valores da interface
    double sx_final = ui->escaleXSpinBox->value();
    double sy_final = ui->escaleYSpinBox->value();

    // Lógica da animação (continua a mesma)
    const int duracao_ms = 1000;
    const int intervalo_ms = 20;
    int passos_totais = duracao_ms / intervalo_ms;
    double fator_x_passo = pow(sx_final, 1.0 / passos_totais);
    double fator_y_passo = pow(sy_final, 1.0 / passos_totais);
    int passos_dados = 0;

    QTimer *timer = new QTimer(this);
    // Note que não precisamos mais capturar "&objetoSelecionado" aqui
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // 2. Itera por TODOS os objetos no displayFile.
        for (ObjetoVirtual &objeto : displayFile) {
            
            // 3. Verifica se o nome do objeto COMEÇA com o nome selecionado.
            if (objeto.nome.startsWith(nomeBaseSelecionado)) {
                
                // 4. Se começar, aplica a transformação de escala.
                objeto.escalonar(fator_x_passo, fator_y_passo);
            }
        }

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}

void MainWindow::on_rotationButton_clicked()
{
    // Pega o NOME do objeto selecionado
    QString nomeBaseSelecionado = ui->objectSelectorComboBox->currentText();
     if (nomeBaseSelecionado.isEmpty()) return;

    // Pega os valores da interface
    double anguloFinal = ui->rotationAngleSpinBox->value();

    // Lógica da animação
    const int duracao_ms = 1000;
    const int intervalo_ms = 20;
    int passos_totais = duracao_ms / intervalo_ms;
    double passo_angulo = anguloFinal / passos_totais;
    int passos_dados = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // Itera por TODOS os objetos no displayFile
        for (ObjetoVirtual &objeto : displayFile) {
            // Se o nome do objeto COMEÇA com o nome selecionado...
            if (objeto.nome.startsWith(nomeBaseSelecionado)) {
                // ...aplica a transformação de rotação!
                objeto.rotacionar(passo_angulo);
            }
        }

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}


void MainWindow::on_escaleEixoButton_clicked()
{
    QString nomeBaseSelecionado = ui->objectSelectorComboBox->currentText();
    if (nomeBaseSelecionado.isEmpty() || nomeBaseSelecionado == "#WINDOW_CAMERA") return;

    // --- PASSO 1: Encontrar o centro comum (mesma lógica da rotação) ---
    QVector<Ponto> todosOsPontosDoObjeto;
    for (const ObjetoVirtual &objeto : displayFile) {
        if (objeto.nome.startsWith(nomeBaseSelecionado)) {
            todosOsPontosDoObjeto.append(objeto.pontos);
        }
    }
    if (todosOsPontosDoObjeto.isEmpty()) return;
    double minX = todosOsPontosDoObjeto[0].x(), maxX = minX;
    double minY = todosOsPontosDoObjeto[0].y(), maxY = minY;
    for (const Ponto &p : todosOsPontosDoObjeto) {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    }
    Ponto centroComum((minX + maxX) / 2.0, (minY + maxY) / 2.0);
    // --------------------------------------------------------------------

    // --- PASSO 2: Configurar a animação ---
    double sx_final = ui->escaleXSpinBox->value();
    double sy_final = ui->escaleYSpinBox->value();
    const int duracao_ms = 1000;
    const int intervalo_ms = 20;
    int passos_totais = duracao_ms / intervalo_ms;
    double fator_x_passo = pow(sx_final, 1.0 / passos_totais);
    double fator_y_passo = pow(sy_final, 1.0 / passos_totais);
    int passos_dados = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // --- PASSO 3: Construir UMA matriz de transformação usando o centro comum ---
        Matriz T_ida = Matriz::criarMatrizTranslacao(-centroComum.x(), -centroComum.y());
        Matriz S_passo = Matriz::criarMatrizEscala(fator_x_passo, fator_y_passo);
        Matriz T_volta = Matriz::criarMatrizTranslacao(centroComum.x(), centroComum.y());
        Matriz M_passo = T_volta * S_passo * T_ida;
        // -------------------------------------------------------------------------

        // --- PASSO 4: Aplicar a MESMA matriz a todas as partes ---
        for (ObjetoVirtual &objeto : displayFile) {
            if (objeto.nome.startsWith(nomeBaseSelecionado)) {
                for (Ponto &p : objeto.pontos) {
                    p = Ponto(M_passo * p);
                }
            }
        }
        // -----------------------------------------------------------------

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}


void MainWindow::on_rotationEixoButton_clicked()
{
    QString nomeBaseSelecionado = ui->objectSelectorComboBox->currentText();
    if (nomeBaseSelecionado.isEmpty() || nomeBaseSelecionado == "#WINDOW_CAMERA") return;

    // --- PASSO 1: Encontrar o centro comum de TODAS as partes do objeto ---
    QVector<Ponto> todosOsPontosDoObjeto;
    for (const ObjetoVirtual &objeto : displayFile) {
        if (objeto.nome.startsWith(nomeBaseSelecionado)) {
            todosOsPontosDoObjeto.append(objeto.pontos);
        }
    }
    if (todosOsPontosDoObjeto.isEmpty()) return;

    // Calcula o centro a partir da bounding box de todos os pontos juntos
    double minX = todosOsPontosDoObjeto[0].x(), maxX = minX;
    double minY = todosOsPontosDoObjeto[0].y(), maxY = minY;
    for (const Ponto &p : todosOsPontosDoObjeto) {
        if (p.x() < minX) minX = p.x();
        if (p.x() > maxX) maxX = p.x();
        if (p.y() < minY) minY = p.y();
        if (p.y() > maxY) maxY = p.y();
    }
    Ponto centroComum((minX + maxX) / 2.0, (minY + maxY) / 2.0);
    // --------------------------------------------------------------------

    // --- PASSO 2: Configurar a animação (sem alterações aqui) ---
    double anguloFinal = ui->rotationAngleSpinBox->value();
    const int duracao_ms = 1000;
    const int intervalo_ms = 20;
    int passos_totais = duracao_ms / intervalo_ms;
    double passo_angulo = anguloFinal / passos_totais;
    int passos_dados = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (passos_dados >= passos_totais) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        // --- PASSO 3: Construir UMA matriz de transformação usando o centro comum ---
        Matriz T_ida = Matriz::criarMatrizTranslacao(-centroComum.x(), -centroComum.y());
        Matriz R_passo = Matriz::criarMatrizRotacao(passo_angulo);
        Matriz T_volta = Matriz::criarMatrizTranslacao(centroComum.x(), centroComum.y());
        Matriz M_passo = T_volta * R_passo * T_ida;
        // -------------------------------------------------------------------------

        // --- PASSO 4: Aplicar a MESMA matriz a todas as partes do objeto ---
        for (ObjetoVirtual &objeto : displayFile) {
            if (objeto.nome.startsWith(nomeBaseSelecionado)) {
                // Em vez de chamar objeto.rotacionarEixo, aplicamos a matriz diretamente
                for (Ponto &p : objeto.pontos) {
                    p = Ponto(M_passo * p);
                }
            }
        }
        // -----------------------------------------------------------------

        passos_dados++;
        ui->TelaDesenho->update();
    });

    timer->start(intervalo_ms);
}

void MainWindow::on_panUpButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double angulo = windowObj.getAnguloEmGraus() * M_PI / 180.0;
    double passo = 10.0;

    // Subir no eixo local da câmera
    double dx = passo * sin(angulo);
    double dy = passo * cos(angulo);

    windowObj.transladar(dx, dy);
    ui->TelaDesenho->update();
}



void MainWindow::on_panDownButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double angulo = windowObj.getAnguloEmGraus() * M_PI / 180.0;
    double passo = 10.0;

    // Descer no eixo local da câmera
    double dx = -passo * sin(angulo);
    double dy = -passo * cos(angulo);

    windowObj.transladar(dx, dy);
    ui->TelaDesenho->update();
}

void MainWindow::on_panRightButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double angulo = windowObj.getAnguloEmGraus() * M_PI / 180.0;
    double passo = 10.0;

    // Direita local (giro +90°)
    double dx = passo * cos(angulo);
    double dy = -passo * sin(angulo);

    windowObj.transladar(dx, dy);
    ui->TelaDesenho->update();
}


void MainWindow::on_panLeftButton_clicked()
{
    if (indiceDaWindow == -1) return;
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];

    double angulo = windowObj.getAnguloEmGraus() * M_PI / 180.0;
    double passo = 10.0;

    // Esquerda local (giro -90°)
    double dx = -passo * cos(angulo);
    double dy = passo * sin(angulo);

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

QVector<ObjetoVirtual> criarBolaPixar(double x_centro, double y_centro, const QString& nome_base) {
    QVector<ObjetoVirtual> partesBola;

    // --- Parte 1: Corpo principal (círculo azul claro) ---
    ObjetoVirtual corpo;
    corpo.nome = nome_base + " - Corpo";
    corpo.tipo = TipoObjeto::Poligono;
    corpo.cor = QColor("#5DADE2"); // Azul Pixar

    int lados = 36; // quantidade de lados para simular o círculo
    double raio = 50.0;
    for (int i = 0; i < lados; ++i) {
        double ang = i * (2 * M_PI / lados);
        corpo.pontos.append(Ponto(raio * cos(ang) + x_centro, raio * sin(ang) + y_centro));
    }
    partesBola.append(corpo);

    // --- Parte 2: Faixa amarela ---
    ObjetoVirtual faixa;
    faixa.nome = nome_base + " - Faixa";
    faixa.tipo = TipoObjeto::Poligono;
    faixa.cor = QColor("#F4D03F"); // Amarelo Pixar

    double raioInterno = 25.0;
    for (int i = 0; i < lados; ++i) {
        double ang = i * (2 * M_PI / lados);
        faixa.pontos.append(Ponto(raioInterno * cos(ang) + x_centro, raioInterno * sin(ang) + y_centro));
    }
    partesBola.append(faixa);

    // --- Parte 3: Estrela vermelha ---
    ObjetoVirtual estrela;
    estrela.nome = nome_base + " - Estrela";
    estrela.tipo = TipoObjeto::Poligono;
    estrela.cor = QColor("#E74C3C"); // Vermelho

    double raioExterno = 20.0;
    double raioInternoEstrela = 8.0;
    int pontas = 5;
    for (int i = 0; i < 2 * pontas; ++i) {
        double ang = i * (M_PI / pontas);
        double r = (i % 2 == 0) ? raioExterno : raioInternoEstrela;
        estrela.pontos.append(Ponto(r * cos(ang) + x_centro, r * sin(ang) + y_centro));
    }
    partesBola.append(estrela);

    return partesBola;
}
