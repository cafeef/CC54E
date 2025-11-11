#ifndef PONTO_H
#define PONTO_H

#include "matriz.h" // Inclui a definição da Matriz

class Ponto {
public:
    // Vetor coluna 4x1
    std::vector<std::vector<double>> dados;

    // Construtor: cria um ponto [x, y, z, 1]
    Ponto(double x = 0.0, double y = 0.0, double z = 0.0);

    // Getters
    double x() const;
    double y() const;
    double z() const;

    // Setters
    void setX(double novoX);
    void setY(double novoY);
    void setZ(double novoZ);
};

#endif // PONTO_H
