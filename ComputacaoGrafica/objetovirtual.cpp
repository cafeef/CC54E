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
    // --- ESTA É A CORREÇÃO ---
    if (this->nome == "#WINDOW_CAMERA") {
        // "Transformação geométrica" da CÂMERA (Pan)
        // Modifica as propriedades da câmera, evitando o "deslize na diagonal"
        this->camera_centro.dados[0][0] += dx;
        this->camera_centro.dados[1][0] += dy;
        this->camera_centro.dados[2][0] += dz;
    } else {
        // "Transformação geométrica" de um OBJETO (Move)
        // (O seu código original de objeto, que está correto)
        Matriz T = Matriz::criarMatrizTranslacao(dx, dy, dz);
        for (Ponto &v : vertices) {
            v = T * v;
        }
    }
}

// Escala 3D: aplica a escala em torno do centro do objeto
void ObjetoVirtual::escalonarEixo(double sx, double sy, double sz) {
    if (this->nome == "#WINDOW_CAMERA") {
        // "Transformação geométrica" da CÂMERA (Zoom)
        // A câmera só tem um zoom uniforme. Usamos 'sx' como o fator.
        this->camera_zoom *= sx;
    } else {
        // "Transformação geométrica" de um OBJETO (Scale)
        // (O seu código original de objeto, que está correto)
        Ponto centro = calcularCentro();
        Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
        Matriz S = Matriz::criarMatrizEscala(sx, sy, sz);
        Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
        Matriz M = T_volta * S * T_ida;

        for (Ponto &v : vertices) {
            v = M * v;
        }
    }
}

// Rotação 3D em X
void ObjetoVirtual::rotacionarEixoX(double anguloGraus) {
    if (this->nome == "#WINDOW_CAMERA") {
        // "Transformação geométrica" da CÂMERA (Tilt)
        this->camera_rotX += anguloGraus;
    } else {
        // "Transformação geométrica" de um OBJETO (Rotate)
        // (O seu código original de objeto, que está correto)
        Ponto centro = calcularCentro();
        Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
        Matriz R = Matriz::criarMatrizRotacaoX(anguloGraus);
        Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
        Matriz M = T_volta * R * T_ida;

        for (Ponto &v : vertices) {
            v = M * v;
        }
    }
}

// Rotação 3D em Y
void ObjetoVirtual::rotacionarEixoY(double anguloGraus) {
    if (this->nome == "#WINDOW_CAMERA") {
        // "Transformação geométrica" da CÂMERA (Orbit)
        this->camera_rotY += anguloGraus;
    } else {
        // "Transformação geométrica" de um OBJETO (Rotate)
        // (O seu código original de objeto, que está correto)
        Ponto centro = calcularCentro();
        Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
        Matriz R = Matriz::criarMatrizRotacaoY(anguloGraus);
        Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
        Matriz M = T_volta * R * T_ida;

        for (Ponto &v : vertices) {
            v = M * v;
        }
    }
}

// Rotação 3D em Z
void ObjetoVirtual::rotacionarEixoZ(double anguloGraus) {
    if (this->nome == "#WINDOW_CAMERA") {
        // "Transformação geométrica" da CÂMERA (Roll)
        this->camera_rotZ += anguloGraus;
    } else {
        // "Transformação geométrica" de um OBJETO (Rotate)
        // (O seu código original de objeto, que está correto)
        Ponto centro = calcularCentro();
        Matriz T_ida = Matriz::criarMatrizTranslacao(-centro.x(), -centro.y(), -centro.z());
        Matriz R = Matriz::criarMatrizRotacaoZ(anguloGraus);
        Matriz T_volta = Matriz::criarMatrizTranslacao(centro.x(), centro.y(), centro.z());
        Matriz M = T_volta * R * T_ida;

        for (Ponto &v : vertices) {
            v = M * v;
        }
    }
}
