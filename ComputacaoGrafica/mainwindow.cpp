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

    // 2. Criar um Ponto
    ObjetoVirtual pontoA;
    pontoA.nome = "Ponto Central";
    pontoA.tipo = TipoObjeto::Ponto;
    pontoA.pontos.append(QPointF(400.0, 300.0)); // Um ponto só tem uma coordenada

    // 3. Criar uma Reta
    ObjetoVirtual reta1;
    reta1.nome = "Linha Diagonal";
    reta1.tipo = TipoObjeto::Reta;
    reta1.pontos.append(QPointF(50.0, 50.0));   // Ponto inicial
    reta1.pontos.append(QPointF(200.0, 200.0)); // Ponto final

    // 4. Criar um Polígono (Triângulo)
    ObjetoVirtual triangulo1;
    triangulo1.nome = "Triângulo de Teste";
    triangulo1.tipo = TipoObjeto::Poligono;
    triangulo1.pontos.append(QPointF(250.0, 250.0)); // Vértice 1
    triangulo1.pontos.append(QPointF(350.0, 250.0)); // Vértice 2
    triangulo1.pontos.append(QPointF(300.0, 350.0)); // Vértice 3

    // 4. Criar um Polígono (Triângulo)
    ObjetoVirtual coracao;
    coracao.nome = "Coração de Teste";
    coracao.tipo = TipoObjeto::Poligono;
    coracao.pontos.append(QPointF(398, 503));
    coracao.pontos.append(QPointF(262, 455));
    coracao.pontos.append(QPointF(140.0, 389.0));
    coracao.pontos.append(QPointF(44, 244));
    coracao.pontos.append(QPointF(119, 101));
    coracao.pontos.append(QPointF(266.0, 94.0));
    coracao.pontos.append(QPointF(398, 145));
    coracao.pontos.append(QPointF(531, 94));
    coracao.pontos.append(QPointF(678, 101));
    coracao.pontos.append(QPointF(760, 189));
    coracao.pontos.append(QPointF(744, 300));
    coracao.pontos.append(QPointF(656, 390));
    coracao.pontos.append(QPointF(535, 456));
    coracao.pontos.append(QPointF(398, 503));

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
