#include "window.h"

Window::Window() : centro(0,0) {
    largura = 200.0;
    altura = 200.0;
    angulo = 0.0;
}

void Window::pan(double dx, double dy)
{
    // O método transladar que já criamos no Ponto é perfeito para isto
    centro.transladar(dx, dy);
}

void Window::zoom(double fator)
{
    // Multiplicamos a largura e altura pelo fator para dar zoom
    largura *= fator;
    altura *= fator;
}

void Window::rotacionar(double anguloEmGraus)
{
    // Apenas somamos ao ângulo atual
    angulo += anguloEmGraus;
}

Ponto Window::getCentro() const
{
    return centro;
}

double Window::getLargura() const
{
    return largura;
}

double Window::getAltura() const
{
    return altura;
}

double Window::getAngulo() const
{
    return angulo;
}
