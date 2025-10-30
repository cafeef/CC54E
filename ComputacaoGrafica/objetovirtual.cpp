#include "objetovirtual.h"
#include <cmath>

// Calcula o centro geométrico (média de todos os vértices)
Ponto ObjetoVirtual::calcularCentro() const {
    if (vertices.isEmpty()) return Ponto(0, 0, 0);

    double somaX = 0, somaY = 0, somaZ = 0;
    for (const Ponto &v : vertices) {
        somaX += v.x();
        somaY += v.y();
        somaZ += v.z();
    }
    int numVertices = vertices.size();
    return Ponto(somaX / numVertices, somaY / numVertices, somaZ / numVertices);
}

// Translação 3D: aplica a matriz de translação a todos os vértices
void ObjetoVirtual::transladar(double dx, double dy, double dz) {
    Matriz T = Matriz::criarMatrizTranslacao(dx, dy, dz);
    for (Ponto &v : vertices) {
        v = T * v;
    }
}

// Escala 3D: aplica a escala em torno do centro do objeto
void ObjetoVirtual::escalonarEixo(double sx, double sy, double sz) {
    Ponto centro = calcularCentro();
    Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
    Matriz S = Matriz::criarMatrizEscala(sx, sy, sz);
    Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
    Matriz M = T_volta * S * T_ida;

    for (Ponto &v : vertices) {
        v = M * v;
    }
}

// Rotação 3D em X: em torno do centro do objeto
void ObjetoVirtual::rotacionarEixoX(double anguloGraus) {
    Ponto centro = calcularCentro();
    Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
    Matriz R = Matriz::criarMatrizRotacaoX(anguloGraus);
    Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
    Matriz M = T_volta * R * T_ida;

    for (Ponto &v : vertices) {
        v = M * v;
    }
}

// Rotação 3D em Y: em torno do centro do objeto
void ObjetoVirtual::rotacionarEixoY(double anguloGraus) {
    Ponto centro = calcularCentro();
    Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
    Matriz R = Matriz::criarMatrizRotacaoY(anguloGraus);
    Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
    Matriz M = T_volta * R * T_ida;

    for (Ponto &v : vertices) {
        v = M * v;
    }
}

// Rotação 3D em Z: em torno do centro do objeto
void ObjetoVirtual::rotacionarEixoZ(double anguloGraus) {
    Ponto centro = calcularCentro();
    Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
    Matriz R = Matriz::criarMatrizRotacaoZ(anguloGraus);
    Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
    Matriz M = T_volta * R * T_ida;

    for (Ponto &v : vertices) {
        v = M * v;
    }
}
