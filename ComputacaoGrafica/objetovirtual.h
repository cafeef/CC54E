// Em objetovirtual.h
#ifndef OBJETOVIRTUAL_H
#define OBJETOVIRTUAL_H

#include <QString>
#include <QColor>
#include <QVector>
#include "ponto.h" // O nosso novo Ponto 4D
#include "face.h"  // A nossa nova struct Face

// Podemos manter o enum, mas adicionar um tipo para 3D
enum class TipoObjeto {
    Ponto,
    Reta,
    Poligono,
    Mesh3D // Novo tipo para modelos 3D
};

class ObjetoVirtual {
public:
    QString nome;
    QColor cor;
    TipoObjeto tipo;

    QVector<Ponto> vertices; // ANTES: chamava-se 'pontos'
    QVector<Face> faces;     // NOVO: para armazenar as faces do 3D

    // Construtor padrão
    ObjetoVirtual() : cor(Qt::white), tipo(TipoObjeto::Poligono) {}

    // Funções de transformação atualizadas para 3D
    void transladar(double dx, double dy, double dz);
    void escalonarEixo(double sx, double sy, double sz);
    void rotacionarEixoX(double anguloGraus);
    void rotacionarEixoY(double anguloGraus);
    void rotacionarEixoZ(double anguloGraus);

    // Função de ajuda para encontrar o centro 3D
    Ponto calcularCentro() const;
};

#endif // OBJETOVIRTUAL_H
