// Em objetovirtual.h
#ifndef OBJETOVIRTUAL_H
#define OBJETOVIRTUAL_H

#include <QString>
#include <QColor>
#include <QVector>
#include "ponto.h"
#include "face.h"

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

    QVector<Ponto> vertices;
    QVector<Face> faces;

    // Construtor padrão
    ObjetoVirtual() : cor(Qt::white), tipo(TipoObjeto::Poligono) {}

    // Funções de transformação 3D
    void transladar(double dx, double dy, double dz);
    void escalonarEixo(double sx, double sy, double sz);
    void rotacionarEixoX(double anguloGraus);
    void rotacionarEixoY(double anguloGraus);
    void rotacionarEixoZ(double anguloGraus);

    // Função de ajuda para encontrar o centro 3D
    Ponto calcularCentro() const;

    // --- Propriedades da Câmera ---
    Ponto camera_centro;
    double camera_rotX = 0.0;
    double camera_rotY = 0.0;
    double camera_rotZ = 0.0;
    double camera_zoom = 1.0;
};

#endif // OBJETOVIRTUAL_H
