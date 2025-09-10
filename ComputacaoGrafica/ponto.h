#ifndef PONTO_H
#define PONTO_H

#include "matriz.h"

class Ponto : public Matriz {
public:
    //Construtor que recebe x e y
    Ponto(double x, double y);
    Ponto(const Matriz &outra);

    //Métodos que retornam os valores de x e y
    double x() const;
    double y() const;

    //Métodos de Transformações Geométricas
    void transladar(double dx, double dy);
    void escalonar(double dx, double dy);
    void rotacionar(double anguloEmGraus);

};

#endif // PONTO_H
