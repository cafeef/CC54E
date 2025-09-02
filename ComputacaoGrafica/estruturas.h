#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#endif // ESTRUTURAS_H

#pragma once // Garante que este ficheiro só é incluído uma vez pelo compilador

#include <QString>   // Para usar strings do Qt (nomes dos objetos)
#include <QPointF>   // Para representar um ponto (x, y) com precisão float
#include <QColor> //Representar a cor de um objeto

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
