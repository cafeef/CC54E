#ifndef WINDOW_H
#define WINDOW_H

#include "ponto.h"

class Window
{
public:
    //Construtor
    Window();

    // --- Métodos de Navegação ---
    // Move o centro da window (Pan)
    void pan(double dx, double dy);

    // Altera o tamanho da window (Zoom)
    void zoom(double fator); // Fator > 1 aproxima, Fator < 1 afasta

    // Rotaciona a window em torno do seu centro
    void rotacionar(double anguloEmGraus);

    // --- Getters ---
    // Funções para obter as propriedades da window
    Ponto getCentro() const;
    double getLargura() const;
    double getAltura() const;
    double getAngulo() const;

private:
    Ponto centro;
    double largura;
    double altura;
    double angulo; // Em graus
};

#endif // WINDOW_H
