#include "ponto.h"

Ponto::Ponto(double x, double y) {
    //Preenche a matriz 3x1 com os valores de x, y e z (sempre 1)
    dados.append(QVector<double>({x}));
    dados.append(QVector<double>({y}));
    dados.append(QVector<double>({1.0}));
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
    Matriz T = Matriz::criarMatrizTranslacao(dx, dy);

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

 void Ponto::MatrizCompostaEscala(double sx, double sy, double dx, double dy)
{
    // Passo 1: Chamar função para criar a matriz indentidade
    Matriz S = Matriz::criarMatrizEscala(sx, sy);

    // Passo 2: Criar a matriz translação 1 com os valores positivos
    Matriz T1 = Matriz::criarMatrizTranslacao(dx, dy);

    // Passo 3: Criar a matriz translação 2 com os valores negativos
    Matriz T2 = Matriz::criarMatrizTranslacao((-1 * dx), (-1 * dy));

    // Passo 4: aplicar a transformação T1*R*T2
    Matriz intermedio = T1 * S;
    Matriz resultado = intermedio * T2;

    for(int i; i < 3; i++){
        for(int j; j < 3; j++){
            printf(resultado.getDados());
        }
    }

    printf("\nsx: %f", sx);
    printf("\nsy: %f", sy);
    printf("\ndx: %f", dx);
    printf("\ndy: %f", dy);
    this->dados = resultado.getDados();
}

void Ponto::MatrizCompostaRotacao(double anguloEmGraus, double dx, double dy)
{
    // Passo 1: Chamar função para criar a matriz indentidade
    Matriz R = Matriz::criarMatrizRotacao(anguloEmGraus);

    // Passo 2: Criar a matriz translação 1 com os valores positivos
    Matriz T1 = Matriz::criarMatrizTranslacao( dx, dy);

    // Passo 3: Criar a matriz translação 2 com os valores negativos
    Matriz T2 = Matriz::criarMatrizTranslacao((-1 * dx), (-1 * dy));

    // Passo 4: aplicar a transformação T1*R*T2
    Matriz intermedio = T1 * R;
    Matriz resultado = intermedio * T2;

    printf("\nângulo: %f", anguloEmGraus);
    printf("\ndx: %f", dx);
    printf("\ndy: %f", dy);


    // Passo 5: Retorne a matriz de rotação
    this->dados = resultado.getDados();
}
