#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <estruturas.h>
#include "window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_translateButton_clicked();

    void on_escaleButton_clicked();

    void on_rotationButton_clicked();

    void on_escaleEixoButton_clicked();

    void on_rotationEixoButton_clicked();

    void on_panLeftButton_clicked();

    void on_panUpButton_clicked();

    void on_panRightButton_clicked();

    void on_panDownButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void on_rotateRightButton_clicked();

    void on_rotateLeftButton_clicked();

private:
    Ui::MainWindow *ui;
    Window minhaWindow;
    void centralizarNaCena();
    QVector<ObjetoVirtual> displayFile;
    QVector<QVector<double>> multiplicacao(const QVector<QVector<double>>& A, const QVector<QVector<double>>& B);
    QVector<QVector<double>> translacao(const QVector<QVector<double>> &matriz, const QVector<double> &valores);
    QVector<QVector<double>> rotacao(const QVector<QVector<double>> &matriz, double angulo);;
    QVector<QVector<double>> escalonar(double sx, double sy, const QVector<QVector<double>>& B);


};
#endif // MAINWINDOW_H
