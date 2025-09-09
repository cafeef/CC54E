#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "estruturas.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // --- Exemplo de criação de objetos ---

    //declaração de coordenadas, uma lista de pontos que um desenho tem. vai servir para atribuir a matriz em PontoMatriz
    QList<double> coordenadas;

    // 2. Criar um Ponto
    ObjetoVirtual pontoA;
    pontoA.nome = "Ponto Central";
    pontoA.tipo = TipoObjeto::Ponto;
    coordenadas = {400, 300};

    //adicionando em pontos cada matriz de coordenada
    for (int i = 0; i < coordenadas.size(); i += 2) {
        pontoA.pontos.append(Ponto(coordenadas[i], coordenadas[i + 1]));
    }

    pontoA.cor = Qt::green;

    // 3. Criar uma Reta
    ObjetoVirtual reta1;
    reta1.nome = "Linha Diagonal";
    reta1.tipo = TipoObjeto::Reta;
    coordenadas.clear(); //limpando a lista para receber as próximas coordenadas do desenho
    coordenadas = {50.0, 50.0, 200.0, 200.0};

    //adicionando em pontos cada matriz de coordenada
    for (int i = 0; i < coordenadas.size(); i += 2) {
        reta1.pontos.append(Ponto(coordenadas[i], coordenadas[i + 1]));
    }
    reta1.cor = Qt::blue;

    // 4. Criar um Polígono (Triângulo)
    ObjetoVirtual triangulo1;
    triangulo1.nome = "Triângulo de Teste";
    triangulo1.tipo = TipoObjeto::Poligono;
    coordenadas.clear(); //limpando a lista para receber as próximas coordenadas do desenho
    coordenadas = {250.0, 250.0, 350.0, 250.0, 300.0, 350.0}; //coordenadas de desenho

    //adicionando em pontos cada matriz de coordenada

    for (int i = 0; i < coordenadas.size(); i += 2) {
        triangulo1.pontos.append(Ponto(coordenadas[i], coordenadas[i + 1]));
    }
    triangulo1.cor = Qt::red;


    // 5. Adicionar os objetos ao Display File
    displayFile.append(pontoA);
    displayFile.append(reta1);
    displayFile.append(triangulo1);

    ui->TelaDesenho->setDisplayFile(&displayFile);


    //Percorrendo o displayFile para adicionar os objetos no combobox (seleção de objetos a serem alterados)
    for (int i = 0; i < displayFile.size(); i++) {
        ui->objectSelectorComboBox->addItem(displayFile[i].nome);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_translateButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double dx, dy;
    dx = ui->translateXSpinBox->value();
    dy = ui->translateYSpinBox->value();
    objetoSelecionado.transladar(dx, dy);
    ui->TelaDesenho->update();

}

void MainWindow::on_escaleButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double sx, sy;
    sx = ui->escaleXSpinBox->value();
    sy = ui->escaleYSpinBox->value();
    objetoSelecionado.escalonar(sx, sy);
    ui->TelaDesenho->update();
}


void MainWindow::on_rotationButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double angulo;
    angulo = ui->rotationAngleSpinBox->value();
    objetoSelecionado.rotacionar(angulo);
    ui->TelaDesenho->update();
}

