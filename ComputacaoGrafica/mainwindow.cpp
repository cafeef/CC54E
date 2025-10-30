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

    // --- CARREGAR OS POKÉMONS ---
    // !!! MUDE ESTES CAMINHOS PARA ONDE VOCÊ GUARDOU OS SEUS FICHEIROS .obj !!!
    QString caminhoPokebola = "Pokemons/Pokeball_Obj.obj";

    ObjetoVirtual pokebola = carregarObjetoOBJ(caminhoPokebola, "Pokebola", Qt::red);

    // --- Posicionar os Pokémons na cena 3D ---
    // (Ajuste estes valores depois de executar pela primeira vez)
    pokebola.escalonarEixo(0.05, 0.05, 0.05); // (Este pode ser grande)
    pokebola.transladar(100, 0, 0);         // Move para a direita

    displayFile.append(pokebola);
    // ------------------------------------

    // Conecta o display file à tela
    ui->TelaDesenho->setDisplayFile(&displayFile);

    // Preenche a ComboBox com os nomes dos objetos
    atualizarComboBoxDeObjetos();
}

MainWindow::~MainWindow() {
    delete ui;
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

// --- SLOTS DE NAVEGAÇÃO (Câmera) ---
// Estes botões agora controlam a câmera na TelaDeDesenho

void MainWindow::on_panUpButton_clicked() {
    ui->TelaDesenho->moverCamera(0, 10, 0); // Pan Cima
}
void MainWindow::on_panDownButton_clicked() {
    ui->TelaDesenho->moverCamera(0, -10, 0); // Pan Baixo
}
void MainWindow::on_panLeftButton_clicked() {
    ui->TelaDesenho->moverCamera(-10, 0, 0); // Pan Esquerda
}
void MainWindow::on_panRightButton_clicked() {
    ui->TelaDesenho->moverCamera(10, 0, 0); // Pan Direita
}

void MainWindow::on_zoomInButton_clicked() {
    ui->TelaDesenho->aplicarZoom(1.1); // Aumenta o zoom
}
void MainWindow::on_zoomOutButton_clicked() {
    ui->TelaDesenho->aplicarZoom(0.9); // Diminui o zoom
}

// Rotação da Câmera (orbitar)
void MainWindow::on_rotateLeftButton_clicked() {
    ui->TelaDesenho->rotacionarCamera(0, -5, 0); // Gira em Y
}
void MainWindow::on_rotateRightButton_clicked() {
    ui->TelaDesenho->rotacionarCamera(0, 5, 0); // Gira em Y
}
// (Você pode querer ligar o pan up/down à rotação em X)
// ui->TelaDesenho->rotacionarCamera(-5, 0, 0); // Gira em X


// --- SLOTS DE TRANSFORMAÇÃO DE OBJETO (3D) ---
// Estes botões transformam o objeto selecionado

void MainWindow::on_translateButton_clicked() {
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return;

    double dx = ui->translateXSpinBox->value();
    double dy = ui->translateYSpinBox->value();

    // --- CORREÇÃO TEMPORÁRIA ---
    // Você precisará adicionar um "translateZSpinBox" na sua UI
    double dz = 0.0; // Valor padrão por enquanto
    // double dz = ui->translateZSpinBox->value(); // A linha original
    // ---------------------------

    displayFile[indice].transladar(dx, dy, dz);
    ui->TelaDesenho->update();
}

void MainWindow::on_rotationEixoButton_clicked() {
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return;

    double angulo = ui->rotationAngleSpinBox->value();
    // Você precisará adicionar botões ou um seletor para os eixos X, Y, Z
    displayFile[indice].rotacionarEixoY(angulo); // Exemplo: rodar em Y
    ui->TelaDesenho->update();
}

void MainWindow::on_escaleEixoButton_clicked() {
    int indice = ui->objectSelectorComboBox->currentIndex();
    if (indice < 0) return;

    double sx = ui->escaleXSpinBox->value();
    double sy = ui->escaleYSpinBox->value();

    // --- CORREÇÃO TEMPORÁRIA ---
    // Você precisará adicionar um "escaleZSpinBox" na sua UI
    double sz = 1.0; // Valor padrão (escala 1.0 não muda nada)
    // double sz = ui->escaleZSpinBox->value(); // A linha original
    // ---------------------------

    // Para escala, valores 0 podem causar problemas. Usamos 1.0 se for 0.
    if (sx == 0) sx = 1.0;
    if (sy == 0) sy = 1.0;
    if (sz == 0) sz = 1.0;

    displayFile[indice].escalonarEixo(sx, sy, sz);
    ui->TelaDesenho->update();
}
