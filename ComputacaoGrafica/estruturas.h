#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#endif // ESTRUTURAS_H

#pragma once // Garante que este ficheiro só é incluído uma vez pelo compilador

#include <QString>   // Para usar strings do Qt (nomes dos objetos)
#include <QPointF>   // Para representar um ponto (x, y) com precisão float
#include <QColor> //Representar a cor de um objeto
#include <QDebug>
#include "ponto.h" //Inclui a biblioteca ponto que criamos

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
 * @brief Estrutura que representa um único objeto virtual a ser desenhado.
 * Contém todas as informações necessárias: nome, tipo e os pontos que o definem.
 */

class ObjetoVirtual {
public:
    //atributos da classe objeto: nome, tipo e coordenadas
    QString nome; //Nome do objeto
    TipoObjeto tipo; //tipo do objeto
    QVector <Ponto> pontos; //um vetor de classe Ponto
    QColor cor; //cor do objeto

    //Métodos das transformações
    void transladar(double dx, double dy) {
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i].transladar(dx, dy);
        }
    }

    void escalonar(double sx, double sy) {
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i].escalonar(sx, sy);
        }
    }

    void rotacionar(double angulo) {
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i].rotacionar(angulo);
        }
    }

};

// O nosso "Display File" será simplesmente um vetor destes objetos.
// Podemos declará-lo noutra parte do código assim:
// QVector<ObjetoVirtual> displayFile;
