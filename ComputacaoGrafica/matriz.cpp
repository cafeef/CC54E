#include "matriz.h"
#include "ponto.h" // Inclui Ponto
#include <cmath>

Matriz::Matriz() {
    // Inicializa como uma matriz identidade 4x4
    dados = std::vector<std::vector<double>>(4, std::vector<double>(4, 0.0));
    dados[0][0] = 1.0;
    dados[1][1] = 1.0;
    dados[2][2] = 1.0;
    dados[3][3] = 1.0;
}

Matriz Matriz::criarIdentidade() {
    return Matriz();
}

Matriz Matriz::criarMatrizTranslacao(double dx, double dy, double dz) {
    Matriz T; // Começa como identidade
    T.dados[0][3] = dx;
    T.dados[1][3] = dy;
    T.dados[2][3] = dz;
    return T;
}

Matriz Matriz::criarMatrizEscala(double sx, double sy, double sz) {
    Matriz S; // Começa como identidade
    S.dados[0][0] = sx;
    S.dados[1][1] = sy;
    S.dados[2][2] = sz;
    return S;
}

Matriz Matriz::criarMatrizRotacaoX(double anguloGraus) {
    double rad = anguloGraus * M_PI / 180.0;
    Matriz R;
    R.dados[1][1] = cos(rad);
    R.dados[1][2] = -sin(rad);
    R.dados[2][1] = sin(rad);
    R.dados[2][2] = cos(rad);
    return R;
}

Matriz Matriz::criarMatrizRotacaoY(double anguloGraus) {
    double rad = anguloGraus * M_PI / 180.0;
    Matriz R;
    R.dados[0][0] = cos(rad);
    R.dados[0][2] = sin(rad);
    R.dados[2][0] = -sin(rad);
    R.dados[2][2] = cos(rad);
    return R;
}

Matriz Matriz::criarMatrizRotacaoZ(double anguloGraus) {
    double rad = anguloGraus * M_PI / 180.0;
    Matriz R;
    R.dados[0][0] = cos(rad);
    R.dados[0][1] = -sin(rad);
    R.dados[1][0] = sin(rad);
    R.dados[1][1] = cos(rad);
    return R;
}

Matriz Matriz::criarMatrizPerspectiva(double fovGraus, double aspect, double near, double far) {
    // Esta é a matriz de projeção em perspectiva padrão (OpenGL style)
    // que mapeia para o SCN (-1 a 1) e coloca o Z no W para a divisão.

    Matriz P; // Começa como identidade 4x4
    for(int i=0; i<4; ++i) for(int j=0; j<4; ++j) P.dados[i][j] = 0.0; // Zera a matriz

    double fovRad = fovGraus * M_PI / 180.0;
    double tanHalfFovy = tan(fovRad / 2.0);

    P.dados[0][0] = 1.0 / (aspect * tanHalfFovy);
    P.dados[1][1] = 1.0 / (tanHalfFovy);
    P.dados[2][2] = -(far + near) / (far - near);
    P.dados[2][3] = -(2.0 * far * near) / (far - near);
    P.dados[3][2] = -1.0;

    return P;
}

Matriz Matriz::operator*(const Matriz& outra) const {
    Matriz resultado;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            resultado.dados[i][j] = 0.0; // Zera o campo
            for (int k = 0; k < 4; ++k) {
                resultado.dados[i][j] += this->dados[i][k] * outra.dados[k][j];
            }
        }
    }
    return resultado;
}

Ponto operator*(const Matriz& M, const Ponto& p) {
    Ponto resultado;
    for (int i = 0; i < 4; ++i) {
        resultado.dados[i][0] = 0.0; // Zera o campo
        for (int k = 0; k < 4; ++k) {
            resultado.dados[i][0] += M.dados[i][k] * p.dados[k][0];
        }
    }

    // Normalização (dividir por w)
    double w = resultado.dados[3][0];
    if (w != 0 && w != 1) {
        resultado.dados[0][0] /= w;
        resultado.dados[1][0] /= w;
        resultado.dados[2][0] /= w;
        resultado.dados[3][0] = 1.0;
    }
    return resultado;
}
