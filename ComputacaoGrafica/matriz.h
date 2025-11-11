#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <QVector>

class Ponto; // Declaração avançada (forward declaration)

class Matriz {
public:
    // Matriz 4x4
    std::vector<std::vector<double>> dados;

    // Construtor: cria uma matriz identidade 4x4
    Matriz();

    // Funções de fábrica para transformações 3D
    static Matriz criarIdentidade();
    static Matriz criarMatrizTranslacao(double dx, double dy, double dz);
    static Matriz criarMatrizEscala(double sx, double sy, double sz);
    static Matriz criarMatrizRotacaoX(double anguloGraus);
    static Matriz criarMatrizRotacaoY(double anguloGraus);
    static Matriz criarMatrizRotacaoZ(double anguloGraus);
    static Matriz criarMatrizPerspectiva(double fovGraus, double aspect, double near, double far);

    // Operador de multiplicação
    Matriz operator*(const Matriz& outra) const;
};

// Operador para multiplicar Matriz * Ponto
Ponto operator*(const Matriz& M, const Ponto& p);

#endif // MATRIZ_H
