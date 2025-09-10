#ifndef MATRIZ_H
#define MATRIZ_H

#include <QVector>
#include <cmath> // Para sin() e cos() na rotação

class Matriz
{
public:
    // --- CONSTRUTORES ---
    // Construtor padrão (cria uma matriz vazia)
    Matriz();
    // Construtor que cria uma matriz com tamanho definido e preenchida com zeros
    Matriz(int linhas, int colunas);
    QVector<QVector<double>> getDados() const;



    // --- OPERAÇÕES ---
    // Sobrecarrega o operador * para que possamos fazer A * B
    Matriz operator*(const Matriz &outra) const;
    void imprimir() const;


    // --- MÉTODOS DE FÁBRICA (STATIC) ---
    // Static significa que podemos chamar estas funções sem precisar de um objeto.
    // Ex: Matriz identidade = Matriz::criarIdentidade(3);

    // Cria uma matriz identidade 3x3
    static Matriz criarIdentidade();
    // Cria uma matriz de translação 3x3
    static Matriz criarMatrizTranslacao(double dx, double dy);
    // Cria uma matriz de escala 3x3
    static Matriz criarMatrizEscala(double sx, double sy);
    // Cria uma matriz de rotação 3x3
    static Matriz criarMatrizRotacao(double anguloEmGraus);
    // Cria uma matriz de escala 3x3
    static Matriz MatrizCompostaEscala(double sx, double sy, double dx, double dy);
    // Cria uma matriz de rotação 3x3
    static Matriz MatrizCompostaRotacao(double anguloEmGraus, double dx, double dy);

protected:
    // Usamos 'protected' para que as classes filhas (como Ponto) possam aceder
    QVector<QVector<double>> dados;
};

#endif // MATRIZ_H
