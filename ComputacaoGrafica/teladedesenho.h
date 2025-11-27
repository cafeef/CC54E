#ifndef TELADEDESENHO_H
#define TELADEDESENHO_H

#include <QWidget>
#include "objetovirtual.h"
#include "matriz.h"

class TelaDeDesenho : public QWidget {
    Q_OBJECT

public:
    enum class ProjecaoTipo {
        ORTOGONAL,
        PERSPECTIVA
    };
    explicit TelaDeDesenho(QWidget *parent = nullptr);

    void setDisplayFile(QVector<ObjetoVirtual> *ptr_df);
    void setIndiceDaWindow(int indice);

    // Constante da margem (pública para a MainWindow poder ler)
    const double MARGEM_VIEWPORT = 20.0;

signals:
    void zoomRequisitado(double fator);

public slots:
    void setProjecao(ProjecaoTipo tipo);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QVector<ObjetoVirtual> *displayFile_ptr = nullptr;
    int indiceDaWindow = -1; // Índice para encontrar a câmera no displayFile

    ProjecaoTipo projecaoAtual = ProjecaoTipo::ORTOGONAL;

    // --- CLIPPING VOLUMÉTRICO (Constantes) ---
    const int INSIDE = 0; // 000000
    const int LEFT   = 1; // 000001
    const int RIGHT  = 2; // 000010
    const int BOTTOM = 4; // 000100
    const int TOP    = 8; // 001000
    const int NEAR   = 16;// 010000
    const int FAR    = 32;// 100000

    // --- CLIPPING VOLUMÉTRICO (Funções) ---
    // Calcula onde o ponto está (dentro, esquerda, direita...)
    int computeOutCode(double x, double y, double z);

    // O algoritmo de Cohen-Sutherland que corta a linha
    // Retorna 'false' se a linha deve ser totalmente rejeitada
    bool clipLine(double &x0, double &y0, double &z0,
                  double &x1, double &y1, double &z1);

    // Função de ajuda para a pipeline 3D
    Matriz calcularMatrizDeVisualizacao() const;
};

#endif // TELADEDESENHO_H
