#ifndef TELADEDESENHO_H
#define TELADEDESENHO_H

#include <QWidget>
#include "objetovirtual.h"
#include "matriz.h"

class TelaDeDesenho : public QWidget {
    Q_OBJECT

public:
    explicit TelaDeDesenho(QWidget *parent = nullptr);
    void setDisplayFile(QVector<ObjetoVirtual> *ptr_df);

public slots:
    // Slots para a navegação 3D (controlados pela MainWindow)
    void rotacionarCamera(double dx, double dy, double dz);
    void moverCamera(double dx, double dy, double dz);
    void aplicarZoom(double fator);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<ObjetoVirtual> *displayFile_ptr = nullptr;

    // Constante da margem (como antes)
    const double MARGEM_VIEWPORT = 20.0;

    // --- Câmera 3D Simples ---
    Ponto cameraPos;    // Posição da câmera no mundo
    double zoom;        // Fator de zoom da projeção ortogonal
    double rotX, rotY;  // Rotação da câmera

    // Função de ajuda para a pipeline 3D
    Matriz calcularMatrizDeVisualizacao() const;
};

#endif // TELADEDESENHO_H
