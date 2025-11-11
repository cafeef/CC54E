#include "ponto.h"

Ponto::Ponto(double x, double y, double z) {
    dados = std::vector<std::vector<double>>(4, std::vector<double>(1, 0.0));
    dados[0][0] = x;
    dados[1][0] = y;
    dados[2][0] = z;
    dados[3][0] = 1.0; // Coordenada homogênea 'w'
}

double Ponto::x() const { return dados[0][0]; }
double Ponto::y() const { return dados[1][0]; }
double Ponto::z() const { return dados[2][0]; }

// --- SETTERS (Escrita) ---

void Ponto::setX(double novoX) {
    if (dados.size() > 0 && dados[0].size() > 0) {
        dados[0][0] = novoX;
    }
}

void Ponto::setY(double novoY) {
    if (dados.size() > 1 && dados[1].size() > 0) {
        dados[1][0] = novoY;
    }
}

void Ponto::setZ(double novoZ) {
    if (dados.size() > 2 && dados[2].size() > 0) {
        dados[2][0] = novoZ;
    }
}
