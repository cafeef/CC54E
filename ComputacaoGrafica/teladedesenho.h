#ifndef TELADEDESENHO_H
#define TELADEDESENHO_H

#include <QWidget>
#include <QVector>
#include "estruturas.h" // Incluímos as nossas estruturas de dados!
#include "window.h"

class TelaDeDesenho : public QWidget
{
    Q_OBJECT // Macro obrigatória para classes Qt

public:
    explicit TelaDeDesenho(QWidget *parent = nullptr);

    // Método público para a MainWindow poder enviar a lista de objetos para a tela
    void setDisplayFile(QVector<ObjetoVirtual> *df_ptr);
    void setWindow(Window *w);

protected:
    // Este é o evento de pintura. O Qt chama-o quando o widget precisa ser redesenhado.
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<ObjetoVirtual> *displayFile_ptr = nullptr; // Ponteiro para o display file
    Window *window_ptr = nullptr;
    Matriz calcularMatrizDeVisualizacao() const;
};

#endif // TELADEDESENHO_H
