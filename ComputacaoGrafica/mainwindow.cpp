#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTimer> // Para as animações

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- Etapa 1: Criar a Window como um Objeto ---
    ObjetoVirtual windowObj;
    windowObj.nome = "#WINDOW_CAMERA";
    windowObj.tipo = TipoObjeto::Mesh3D; // É um "objeto"
    // Os vértices e faces ficam vazios, pois ela não será desenhada.
    // O estado inicial é definido pelas suas propriedades de câmera:
    windowObj.camera_centro = Ponto(0, 0, 500); // Posição Z afastada
    windowObj.camera_zoom = 1.0; // Zoom inicial padrão

    displayFile.append(windowObj);
    indiceDaWindow = displayFile.size() - 1; // Guarda o índice

    // --- CARREGAR OS POKÉMONS ---
    // !!! MUDE ESTES CAMINHOS PARA ONDE VOCÊ GUARDOU OS SEUS FICHEIROS .obj !!!
    //QString caminhoPokebola = ":/Pokemons/Pokeball_Obj.obj";
    //QString caminhoPsyduck = ":/Pokemons/psyduck.obj";
    QString caminhoUmbreonLowPoly = ":/Pokemons/UmbreonLowPoly.obj";
    QString caminhoCharizard = ":/Pokemons/charizard.obj";
    QString caminhoPikachu = ":/Pokemons/pikachu.obj";

    //ObjetoVirtual pokebola = carregarObjetoOBJ(caminhoPokebola, "Pokebola", Qt::red);
    ObjetoVirtual umbreonlow = carregarObjetoOBJ(caminhoUmbreonLowPoly, "Umbreon Low", Qt::white);
    ObjetoVirtual pikachu = carregarObjetoOBJ(caminhoPikachu, "Pikachu", Qt::yellow);
    ObjetoVirtual charizard = carregarObjetoOBJ(caminhoCharizard, "Charizard", QColorConstants::Svg::orange);

    // --- Posicionar os Pokémons na cena 3D ---
    // (Ajuste estes valores depois de executar pela primeira vez)
    charizard.escalonarEixo(0.3, 0.3, 0.3);
    charizard.transladar(-5, 0, 0);
    charizard.rotacionarEixoX(90);
    pikachu.escalonarEixo(1.1, 1.1, 1.1);
    pikachu.transladar(5, -1, 0);


    //displayFile.append(pokebola);
    displayFile.append(umbreonlow);
    displayFile.append(charizard);
    displayFile.append(pikachu);
    // ------------------------------------

    // Conecta o display file à tela
    ui->TelaDesenho->setDisplayFile(&displayFile);
    ui->TelaDesenho->setIndiceDaWindow(indiceDaWindow); // Diz à tela onde está a câmera

    ajustarWindowParaCena(); // Ajusta o zoom e centro da câmera

    // Preenche a ComboBox com os nomes dos objetos
    atualizarComboBoxDeObjetos();
}

MainWindow::~MainWindow() {
    delete ui;
}

// --- Esta é a sua nova função de "Enquadrar Cena" ---
void MainWindow::ajustarWindowParaCena() {
    if (indiceDaWindow == -1 || displayFile.size() <= 1) return;

    // 1. Encontra o Bounding Box 3D de todos os objetos (menos a câmera)
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();
    bool algumPontoEncontrado = false;

    for (int i = 0; i < displayFile.size(); ++i) {
        if (i == indiceDaWindow) continue; // Pula a câmera
        for (const Ponto &v : displayFile[i].vertices) {
            if (v.x() < minX) minX = v.x();
            if (v.x() > maxX) maxX = v.x();
            if (v.y() < minY) minY = v.y();
            if (v.y() > maxY) maxY = v.y();
            algumPontoEncontrado = true;
        }
    }
    if (!algumPontoEncontrado) return;

    // 2. Calcula o centro e o tamanho da cena
    Ponto centroCena((minX + maxX) / 2.0, (minY + maxY) / 2.0, 0); // Focamos em X e Y
    double larguraCena = maxX - minX;
    double alturaCena = maxY - minY;

    if (larguraCena == 0 || alturaCena == 0) return;

    // 3. Pega a área da viewport da TelaDeDesenho
    double vp_largura = ui->TelaDesenho->width() - 2 * ui->TelaDesenho->MARGEM_VIEWPORT;
    double vp_altura = ui->TelaDesenho->height() - 2 * ui->TelaDesenho->MARGEM_VIEWPORT;

    // 4. Calcula o fator de zoom necessário
    // (Lembre-se: zoom = 1/r, então r = 1/zoom)
    // O raio de visão 'r' precisa de ser metade do maior lado da cena.
    double r_necessario = std::max(larguraCena, alturaCena) / 2.0;

    // Adiciona uma margem de 10%
    r_necessario *= 1.1;

    // O zoom é o inverso do raio
    double novo_zoom = 1.0 / r_necessario;

    // 5. Atualiza o objeto Window
    ObjetoVirtual &windowObj = displayFile[indiceDaWindow];
    windowObj.camera_centro = Ponto(centroCena.x(), centroCena.y(), 500); // Centra a câmera e afasta em Z
    windowObj.camera_zoom = novo_zoom; // Define o zoom correto
}

// --- Carregador de .obj ---
ObjetoVirtual MainWindow::carregarObjetoOBJ(const QString& caminhoArquivo, const QString& nomeObjeto, QColor cor) {
    ObjetoVirtual objeto;
    objeto.nome = nomeObjeto;
    objeto.cor = cor;
    objeto.tipo = TipoObjeto::Mesh3D;

    QFile arquivo(caminhoArquivo);
    if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "ERRO: Não foi possível abrir o arquivo OBJ:" << caminhoArquivo;
        return objeto;
    }

    QVector<Ponto> vertices_temp; // Armazena vértices na ordem do arquivo

    QTextStream in(&arquivo);
    while (!in.atEnd()) {
        QString linha = in.readLine().trimmed();
        QStringList partes = linha.split(' ', Qt::SkipEmptyParts);
        if (partes.isEmpty()) continue;

        if (partes[0] == "v") { // Vértice
            if (partes.size() >= 4) {
                vertices_temp.append(Ponto(partes[1].toDouble(), partes[2].toDouble(), partes[3].toDouble()));
            }
        } else if (partes[0] == "f") { // Face
            if (partes.size() >= 4) {
                Face face;
                for (int i = 1; i < partes.size(); ++i) {
                    QStringList indicesStr = partes[i].split('/');
                    int indiceVertice = indicesStr[0].toInt();
                    face.indicesVertices.append(indiceVertice - 1); // .obj é 1-based
                }
                objeto.faces.append(face);
            }
        }
    }
    arquivo.close();

    // Copia os vértices para o objeto final
    // (Alguns .obj definem vértices que não são usados, mas esta é a forma mais simples)
    objeto.vertices = vertices_temp;

    qInfo() << "Objeto" << nomeObjeto << "carregado com" << objeto.vertices.size() << "vértices e" << objeto.faces.size() << "faces.";
    return objeto;
}

void MainWindow::atualizarComboBoxDeObjetos() {
    ui->objectSelectorComboBox->clear();
    for (const ObjetoVirtual &objeto : displayFile) {
        ui->objectSelectorComboBox->addItem(objeto.nome);
    }
}

// --- SLOTS DE TRANSFORMAÇÃO DE OBJETO (3D) ---
// Estes botões transformam o objeto selecionado

// Em mainwindow.cpp

void MainWindow::on_translateButton_clicked() {
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return;

    double dx = ui->translateXSpinBox->value();
    double dy = ui->translateYSpinBox->value();

    // Lê o valor do novo SpinBox para Z
    double dz = ui->translateZSpinBox->value();

    displayFile[indice].transladar(dx, dy, dz);
    ui->TelaDesenho->update();
}

void MainWindow::on_rotationEixoButton_clicked()
{
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return; // Nenhum objeto selecionado

    // 1. Lê os valores de ângulo dos três novos SpinBoxes
    double anguloX = ui->rotationXSpinBox->value();
    double anguloY = ui->rotationYSpinBox->value();
    double anguloZ = ui->rotationZSpinBox->value();

    // 2. Aplica as rotações, uma por uma, se o valor for diferente de zero.
    //    A ordem importa (normalmente Z, depois Y, depois X),
    //    mas aplicar sequencialmente assim também funciona.

    if (anguloX != 0.0) {
        displayFile[indice].rotacionarEixoX(anguloX);
    }

    if (anguloY != 0.0) {
        displayFile[indice].rotacionarEixoY(anguloY);
    }

    if (anguloZ != 0.0) {
        displayFile[indice].rotacionarEixoZ(anguloZ);
    }

    // 4. Atualiza a tela para mostrar a mudança
    ui->TelaDesenho->update();
}

void MainWindow::on_escaleEixoButton_clicked() {
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return;

    double sx = ui->escaleXSpinBox->value();
    double sy = ui->escaleYSpinBox->value();

    // Lê o valor do novo SpinBox para Z
    double sz = ui->escaleZSpinBox->value();

    // Proteção contra escala 0
    if (sx == 0) sx = 1.0;
    if (sy == 0) sy = 1.0;
    if (sz == 0) sz = 1.0;

    displayFile[indice].escalonarEixo(sx, sy, sz);
    ui->TelaDesenho->update();
}
