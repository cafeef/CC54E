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
    QVector <double> valores = {dx, dy};
    for(int i = 0; i < objetoSelecionado.pontos.size(); i++) {
        objetoSelecionado.pontos[i].ponto = this->translacao(objetoSelecionado.pontos[i].ponto, valores);
    }
    ui->TelaDesenho->update();

}

//método de translação, recebendo como parametro a matriz e o vetor, utilizando a função de mult.
QVector<QVector<double>> MainWindow::translacao(const QVector<QVector<double>> &matriz, const QVector<double> &valores){
    int linhas = matriz.size();

    //inicializa a matriz identidade com zeros
    QVector<QVector<double>> identidade(linhas, QVector<double>(linhas, 0));

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < linhas; j++){
            if(j == i){
                //monta a coluna principal com 1
                identidade[i][j] = 1;
            } else if(j == (linhas - 1)){ // se estiver na última coluna, coloca o valor do fator de deslocamento
                identidade[i][j] = valores[i];
            } else { // completa o restante com zero
                identidade[i][j] = 0;
            }
        }
    }
    // multiplicação
    QVector<QVector<double>> resultado = multiplicacao(identidade, matriz);
    return resultado;
}

QVector<QVector<double>> MainWindow::rotacao(const QVector<QVector<double>> &matriz, double angulo) {
    int linhas = 3; //limitado a 2D, ou seja matriz 3x3

    // inicializa a matriz com zero
    QVector<QVector<double>> identidade(linhas, QVector<double>(linhas, 0));

    // preenchendo matriz para a rotação
    identidade[0][0] = cos(angulo);
    identidade[0][1] = -sin(angulo);
    identidade[0][2] = 0;

    identidade[1][0] = sin(angulo);
    identidade[1][1] = cos(angulo);
    identidade[1][2] = 0;

    identidade[2][0] = 0;
    identidade[2][1] = 0;
    identidade[2][2] = 1;

    // multiplica matriz de rotação pelos pontos
    QVector<QVector<double>> resultado = multiplicacao(identidade, matriz);
    return resultado;
}


QVector<QVector<double>> MainWindow:: escalonar(double sx, double sy, const QVector<QVector<double>>& B) {
    QVector<QVector<double>> matrizEscala = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };

    QVector<QVector<double>> resultado = multiplicacao(matrizEscala, B);
    return resultado;
}

void MainWindow::on_escaleButton_clicked()
{
    int indiceSelecionado = ui->objectSelectorComboBox->currentIndex();
    ObjetoVirtual &objetoSelecionado = displayFile[indiceSelecionado];
    double sx, sy;
    sx = ui->escaleXSpinBox->value();
    sy = ui->escaleYSpinBox->value();
    for(int i = 0; i < objetoSelecionado.pontos.size(); i++) {
        PontoMatriz &ponto_original = objetoSelecionado.pontos[i];

        // Chama a sua função de escalar
        QVector<QVector<double>> ponto_novo_matriz = this->escalonar(sx, sy, ponto_original.ponto);

        // Atualiza o ponto do objeto com o novo resultado
        ponto_original.ponto = ponto_novo_matriz;

    }
    ui->TelaDesenho->update();
}

