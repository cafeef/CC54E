#ifndef PONTO_H
#define PONTO_H

#include "matriz.h"

class Ponto : public Matriz {
public:
    //Construtor que recebe x e y
    Ponto(double x, double y);

    //Métodos que retornam os valores de x e y
    double x() const;
    double y() const;

    //Métodos de Transformações Geométricas
    void transladar(double dx, double dy);
    void escalonar(double dx, double dy);
    void rotacionar(double anguloEmGraus);

    // Cria uma matriz de escala 3x3
    void MatrizCompostaEscala(double sx, double sy, double dx, double dy);
    // Cria uma matriz de rotação 3x3
    void MatrizCompostaRotacao(double anguloEmGraus, double dx, double dy);

};

#endif // PONTO_H
