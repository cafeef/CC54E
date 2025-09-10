#include "ponto.h"

Ponto::Ponto(double x, double y) {
    //Preenche a matriz 3x1 com os valores de x, y e z (sempre 1)
    dados.append(QVector<double>({x}));
    dados.append(QVector<double>({y}));
    dados.append(QVector<double>({1.0}));
}

Ponto::Ponto(const Matriz &outra)
{
    // Acessa os dados da matriz 'outra' através do getter público
    this->dados = outra.getDados();
}

double Ponto::x() const {
    return dados[0][0]; //retorna o valor de x
}

double Ponto::y() const {
    return dados[1][0]; //retorna o valor de y
}

void Ponto::transladar(double dx, double dy)
{
    // 1. Crie a matriz de translação usando a nossa função de fábrica estática da classe Matriz.
    Matriz T = Matriz::criarMatrizTranslacao(dx, -dy);

    // 2. A classe Ponto herdou a capacidade de ser multiplicada.
    //    Multiplicamos a matriz de translação (T) pelo ponto atual.
    //    O "ponto atual" é o próprio objeto, que é referenciado por '*this'.
    Matriz resultado = T * (*this);

    // 3. Atualize os dados do ponto atual com os dados da matriz resultado.
    //    Lembre-se que 'resultado' é um objeto Matriz, e os dados estão dentro dele.
    this->dados = resultado.getDados();
}

void Ponto::escalonar(double sx, double sy)
{
    // 1. Crie a matriz de translação usando a nossa função de fábrica estática da classe Matriz.
    Matriz E = Matriz::criarMatrizEscala(sx, sy);

    // 2. A classe Ponto herdou a capacidade de ser multiplicada.
    //    Multiplicamos a matriz de translação (T) pelo ponto atual.
    //    O "ponto atual" é o próprio objeto, que é referenciado por '*this'.
    Matriz resultado = E * (*this);

    // 3. Atualize os dados do ponto atual com os dados da matriz resultado.
    //    Lembre-se que 'resultado' é um objeto Matriz, e os dados estão dentro dele.
    this->dados = resultado.getDados();
}

void Ponto::rotacionar(double anguloEmGraus)
{
    // 1. Crie a matriz de translação usando a nossa função de fábrica estática da classe Matriz.
    Matriz R = Matriz::criarMatrizRotacao(anguloEmGraus);

    // 2. A classe Ponto herdou a capacidade de ser multiplicada.
    //    Multiplicamos a matriz de translação (T) pelo ponto atual.
    //    O "ponto atual" é o próprio objeto, que é referenciado por '*this'.
    Matriz resultado = R * (*this);

    // 3. Atualize os dados do ponto atual com os dados da matriz resultado.
    //    Lembre-se que 'resultado' é um objeto Matriz, e os dados estão dentro dele.
    this->dados = resultado.getDados();
}
