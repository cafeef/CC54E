#include "matriz.h"

Matriz::Matriz() {

}

Matriz::Matriz(int linhas, int colunas) {
    dados = QVector<QVector<double>>(linhas, QVector<double>(colunas, 0.0));
}

Matriz Matriz::operator*(const Matriz &outra) const
{
    if (this->dados.isEmpty() || outra.dados.isEmpty()){
        return {};
    }

    else {

        int colunasA = this->dados[0].size();
        int linhasB = outra.dados.size();


        if (colunasA == linhasB){

            int linhasA = this->dados.size();
            int colunasB = outra.dados[0].size();

            // Inicializa matriz resultado (linhasA x colunasB) com zeros
            Matriz R = Matriz(linhasA, colunasB);

            for (int i = 0; i < linhasA; i++) {
                for (int j = 0; j < colunasB; j++) {
                    for (int k = 0; k < colunasA; k++) {
                        R.dados[i][j] += this->dados[i][k] * outra.dados[k][j];
                    }
                }
            }

            return R;
        }

        else{
            return {};
        }

    }}

QVector<QVector<double>> Matriz::getDados() const
{
    return dados;
}

Matriz Matriz::criarIdentidade()
{
    // Passo 1: Crie uma matriz 3x3 chamada 'identidade'
    Matriz identidade = Matriz(3, 3);

    // Passo 2: Use um for loop para percorrer a diagonal
    for (int i = 0; i < 3; i++) {
        identidade.dados[i][i] = 1.0; // Modifica só a diagonal
    }

    // Passo 3: Retorne a matriz
    return identidade;
}

Matriz Matriz::criarMatrizTranslacao(double dx, double dy)
{
    // Passo 1: Comece com uma matriz identidade
    Matriz T = Matriz::criarIdentidade();

    // Passo 2: Altere as células corretas para receber dx e dy
    T.dados[0][2] = dx;
    T.dados[1][2] = dy;

    // Passo 3: Retorne a matriz de translação
    return T;
}

Matriz Matriz::criarMatrizEscala(double sx, double sy)
{
    // Passo 1: Comece com uma matriz identidade
    Matriz S = Matriz::criarIdentidade();

    // Passo 2: Altere as células corretas para receber sx e sy
    S.dados[0][0] = sx;
    S.dados[1][1] = sy;

    // Passo 3: Retorne a matriz de escala
    return S;
}

Matriz Matriz::criarMatrizRotacao(double anguloEmGraus)
{
    // Passo 1: Converter graus para radianos
    double anguloRad = anguloEmGraus * M_PI / 180.0;

    // Passo 2: Calcular o seno e o cosseno UMA VEZ para ser mais eficiente
    double cosTheta = cos(anguloRad);
    double sinTheta = sin(anguloRad);

    // Passo 3: Comece com uma matriz identidade
    Matriz R = Matriz::criarIdentidade();

    // Passo 4: Altere as quatro células do canto superior esquerdo
    R.dados[0][0] = cosTheta;
    R.dados[0][1] = -sinTheta;
    R.dados[1][0] = sinTheta;
    R.dados[1][1] = cosTheta;

    // Passo 5: Retorne a matriz de rotação
    return R;
}
