#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#endif // ESTRUTURAS_H

#pragma once // Garante que este ficheiro só é incluído uma vez pelo compilador

#include <QString>   // Para usar strings do Qt (nomes dos objetos)
#include <QPointF>   // Para representar um ponto (x, y) com precisão float
#include <QColor> //Representar a cor de um objeto
#include <QDebug>
#include "ponto.h" //Inclui a biblioteca ponto que criamos

/**
 * @brief Define os tipos de objetos geométricos que podemos desenhar.
 * Usar um enum torna o código mais seguro e legível do que usar strings.
 */
enum class TipoObjeto {
    Ponto,
    Reta,
    Poligono
};

/**
 * @brief Estrutura que representa um único objeto virtual a ser desenhado.
 * Contém todas as informações necessárias: nome, tipo e os pontos que o definem.
 */

class ObjetoVirtual {
public:
    //atributos da classe objeto: nome, tipo e coordenadas
    QString nome; //Nome do objeto
    TipoObjeto tipo; //tipo do objeto
    QVector <Ponto> pontos; //um vetor de classe Ponto
    QColor cor; //cor do objeto

    double getAnguloEmGraus() const
    {
        // Se não tivermos pontos suficientes para definir um ângulo, retorna 0
        if (pontos.size() < 2) {
            return 0.0;
        }

        // Calcula o ângulo da primeira aresta do objeto (p0 -> p1)
        const Ponto& p0 = pontos[0];
        const Ponto& p1 = pontos[1];
        double dy = p1.y() - p0.y();
        double dx = p1.x() - p0.x();

        // atan2 nos dá o ângulo em radianos, convertemos para graus
        return std::atan2(dy, dx) * 180.0 / M_PI;
    }

    //Métodos das transformações
    void transladar(double dx, double dy) {
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i].transladar(dx, dy);
        }
    }

    void escalonar(double sx, double sy) {
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i].escalonar(sx, sy);
        }
    }

    void rotacionar(double angulo) {
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i].rotacionar(angulo);
        }
    }

    void escalonarEixo(double sx, double sy) {
        Ponto centro = calcularCentro();
        Matriz R = Matriz::MatrizCompostaEscala(sx, sy, centro.x(), centro.y());
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i] = Ponto(R * pontos[i]);
            printf("Novo ponto: (%.1f, %.1f)\n", pontos[i].x(), pontos[i].y());
        }
    }

    void rotacionarEixo(double anguloEmGraus) {
        Ponto centro = calcularCentro();
        Matriz R = Matriz::MatrizCompostaRotacao(anguloEmGraus, centro.x(), centro.y());
        for(int i = 0; i < pontos.size(); i++) {
            pontos[i] = Ponto(R * pontos[i]);
            printf("Novo ponto: (%.1f, %.1f)\n", pontos[i].x(), pontos[i].y());
        }
    }

    Ponto calcularCentro() {
        int quantidadePontos = pontos.size();
        double x = 0, y = 0;
        for(int i = 0; i < quantidadePontos; i++) {
            x += pontos[i].x();
            y += pontos[i].y();
        }
        x = x / quantidadePontos;
        y = y / quantidadePontos;
        Ponto centro = Ponto(x, y);
        return centro;
    }

    void imprimir() const {
        printf("Objeto: %s\n", nome.toStdString().c_str());
        for(int i=0; i<pontos.size(); ++i) {
            printf("  Ponto %d: (%.1f, %.1f)\n", i, pontos[i].x(), pontos[i].y());
        }
    }

};

// O nosso "Display File" será simplesmente um vetor destes objetos.
// Podemos declará-lo noutra parte do código assim:
// QVector<ObjetoVirtual> displayFile;
