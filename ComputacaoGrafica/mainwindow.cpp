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

    // 1. Declarar o nosso Display File (pode ser uma variável membro da classe MainWindow)
    QVector<ObjetoVirtual> displayFile;

    //declaração de coordenadas, uma lista de pontos que um desenho tem. vai servir para atribuir a matriz em PontoMatriz
    QList<double> coordenadas;

    // 2. Criar um Ponto
    ObjetoVirtual pontoA;
    pontoA.nome = "Ponto Central";
    pontoA.tipo = TipoObjeto::Ponto;
    coordenadas = {400, 300};

    //adicionando em pontos cada matriz de coordenada
    for (int i = 0; i < coordenadas.size(); i += 2) {
        pontoA.pontos.append(PontoMatriz(coordenadas[i], coordenadas[i + 1]));
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
        reta1.pontos.append(PontoMatriz(coordenadas[i], coordenadas[i + 1]));
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
        triangulo1.pontos.append(PontoMatriz(coordenadas[i], coordenadas[i + 1]));
    }
    triangulo1.cor = Qt::red;

    // 4. Criar um Polígono
    ObjetoVirtual coracao;
    coracao.nome = "Coração de Teste";
    coracao.tipo = TipoObjeto::Poligono;
    coordenadas.clear();
    coordenadas = {
        398.0, 503.0,
        262.0, 455.0,
        140.0, 389.0,
        44.0, 244.0,
        119.0, 101.0,
        266.0, 94.0,
        398.0, 145.0,
        531.0, 94.0,
        678.0, 101.0,
        760.0, 189.0,
        744.0, 300.0,
        656.0, 390.0,
        535.0, 456.0,
        398.0, 503.0
    };

    //adicionando em pontos cada matriz de coordenada
    for (int i = 0; i < coordenadas.size(); i += 2) {
        coracao.pontos.append(PontoMatriz(coordenadas[i], coordenadas[i + 1]));
    }
    coracao.cor = Qt::red;

    // 5. Adicionar os objetos ao Display File
    displayFile.append(pontoA);
    displayFile.append(reta1);
    displayFile.append(coracao);

    ui->TelaDesenho->setDisplayFile(displayFile);

}

MainWindow::~MainWindow()
{
    delete ui;
}
