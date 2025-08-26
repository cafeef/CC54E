#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#endif // ESTRUTURAS_H

#pragma once // Garante que este ficheiro só é incluído uma vez pelo compilador

#include <QString>   // Para usar strings do Qt (nomes dos objetos)
#include <QVector>   // Para usar listas/vetores do Qt (lista de pontos)
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
 * @brief Estrutura que representa um único objeto virtual a ser desenhado.
 * Contém todas as informações necessárias: nome, tipo e os pontos que o definem.
 */
struct ObjetoVirtual {
    QString nome;         // Nome do objeto, ex: "Triângulo 1"
    TipoObjeto tipo;      // O tipo do objeto (Ponto, Reta ou Poligono)
    QVector<QPointF> pontos; // Lista de pontos que definem a geometria do objeto
    QColor cor; //cor do objeto
};

// O nosso "Display File" será simplesmente um vetor destes objetos.
// Podemos declará-lo noutra parte do código assim:
// QVector<ObjetoVirtual> displayFile;
