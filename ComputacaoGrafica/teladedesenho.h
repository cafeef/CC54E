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

    // Função de ajuda para a pipeline 3D
    Matriz calcularMatrizDeVisualizacao() const;
};

#endif // TELADEDESENHO_H
