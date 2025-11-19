#include "objetovirtual.h"

// Translação 3D
void ObjetoVirtual::transladar(double dx, double dy, double dz) {
    if (this->nome == "#WINDOW_CAMERA") {
        // LÓGICA DA CÂMERA (Pan / Zoom Perspectiva)
        // Modifica as propriedades da câmera
        this->camera_centro.setX( this->camera_centro.x() + dx );
        this->camera_centro.setY( this->camera_centro.y() + dy );
        this->camera_centro.setZ( this->camera_centro.z() + dz );
    } else {
        // LÓGICA DO OBJETO (Pokémon)
        Matriz T = Matriz::criarMatrizTranslacao(dx, dy, dz);
        for (Ponto &v : vertices) {
            v = T * v;
        }
    }
}

// Escala 3D
void ObjetoVirtual::escalonarEixo(double sx, double sy, double sz) {

    if (this->nome == "#WINDOW_CAMERA") {
        // LÓGICA DA CÂMERA (Zoom Ortogonal)
        // A câmera só tem um zoom uniforme. Usamos 'sx' como o fator.
        this->camera_zoom *= sx; // sx pode ser 1.1 ou 0.9
    } else {
        // LÓGICA DO OBJETO (Pokémon)
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
        // LÓGICA DA CÂMERA
        this->camera_rotX += anguloGraus;
    } else {
        // LÓGICA DO OBJETO (Pokémon)
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
        // LÓGICA DA CÂMERA (Orbit)
        this->camera_rotY += anguloGraus;
    } else {
        // LÓGICA DO OBJETO (Pokémon)
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
        // LÓGICA DA CÂMERA (Roll)
        this->camera_rotZ += anguloGraus;
    } else {
        // LÓGICA DO OBJETO (Pokémon)
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

// Calcula o centro geométrico (média de todos os vértices)
Ponto ObjetoVirtual::calcularCentro() const {
    // Se o objeto não tiver vértices, retorna a origem (0,0,0)
    if (vertices.isEmpty()) {
        return Ponto(0, 0, 0);
    }

    double somaX = 0, somaY = 0, somaZ = 0;

    // Soma as coordenadas de todos os vértices
    for (const Ponto &v : vertices) {
        somaX += v.x();
        somaY += v.y();
        somaZ += v.z();
    }

    int numVertices = vertices.size();

    // Retorna a média
    return Ponto(somaX / numVertices, somaY / numVertices, somaZ / numVertices);
}
