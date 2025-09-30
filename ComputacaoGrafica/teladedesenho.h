#ifndef TELADEDESENHO_H
#define TELADEDESENHO_H

#include <QWidget>
#include <QVector>
#include "estruturas.h" // Incluímos as nossas estruturas de dados!

class TelaDeDesenho : public QWidget
{
    Q_OBJECT // Macro obrigatória para classes Qt

public:
    explicit TelaDeDesenho(QWidget *parent = nullptr);

    // Método público para a MainWindow poder enviar a lista de objetos para a tela
    void setDisplayFile(QVector<ObjetoVirtual> *df_ptr);

protected:
    // Este é o evento de pintura. O Qt chama-o quando o widget precisa ser redesenhado.
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<ObjetoVirtual> *displayFile_ptr = nullptr; // Ponteiro para o display file
    void calcularMatrizDeVisualizacao(Matriz& m_norm, Matriz& m_vp) const;

    // --- CONSTANTES PARA O ALGORITMO DE RECORTE ---
    const int DENTRO = 0;   // 0000
    const int ESQUERDA = 1; // 0001
    const int DIREITA = 2;  // 0010
    const int ABAIXO = 4;   // 0100
    const int ACIMA = 8;    // 1000
    // -------------------------------------------

    // --- FUNÇÕES DE AJUDA PARA O RECORTE ---
    int calcularOutcode(const Ponto &p) const;
    bool clipCohenSutherland(Ponto &p1, Ponto &p2) const;

};

#endif // TELADEDESENHO_H
