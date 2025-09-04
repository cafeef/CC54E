#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#endif // ESTRUTURAS_H

#pragma once // Garante que este ficheiro só é incluído uma vez pelo compilador

#include <QString>   // Para usar strings do Qt (nomes dos objetos)
#include <QPointF>   // Para representar um ponto (x, y) com precisão float
#include <QColor> //Representar a cor de um objeto
#include <cmath>  // para sin, cos

/**
 * @brief Define os tipos de objetos geométricos que podemos desenhar.
 * Usar um enum torna o código mais seguro e legível do que usar strings.
 */
enum class TipoObjeto {
    Ponto,
    Reta,
    Poligono
};

/**
 * @brief Classe que representa cada ponto como uma matriz, futuramente pode ter as transformações geométricas.
 */

class PontoMatriz {
public:
    //matriz de cada ponto
    double ponto[3][1];

    // Construtor para facilitar a criação de pontos
    PontoMatriz(double x_inicial, double y_inicial) {
        ponto[0][0] = x_inicial;
        ponto[1][0] = y_inicial;
        ponto[2][0] = 1;
    }


    //metodos para ler a coordenada x ou y de uma matriz
    double x() const {
        return ponto[0][0];
    }

    double y() const {
        return ponto[1][0];
    }

    //método de translação, recebendo como parametro a matriz e o vetor, utilizando a função de mult.
    void translacao(const QVector<QVector<double>> &matriz, const QVector<double> &valores){
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
    }

    void rotacao(const QVector<QVector<double>> &matriz, double angulo) {
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
    }

};

/**
 * @brief Estrutura que representa um único objeto virtual a ser desenhado.
 * Contém todas as informações necessárias: nome, tipo e os pontos que o definem.
 */

class ObjetoVirtual {
public:
    //atributos da classe objeto: nome, tipo e coordenadas
    QString nome; //Nome do objeto
    TipoObjeto tipo; //tipo do objeto
    QVector <PontoMatriz> pontos; //um vetor de classe PontoMatriz para representar todos os pontos
    QColor cor; //cor do objeto
};

// O nosso "Display File" será simplesmente um vetor destes objetos.
// Podemos declará-lo noutra parte do código assim:
// QVector<ObjetoVirtual> displayFile;
