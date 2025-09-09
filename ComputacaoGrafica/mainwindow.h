#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <estruturas.h>

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

private:
    Ui::MainWindow *ui;
    QVector<ObjetoVirtual> displayFile;
    QVector<QVector<double>> multiplicacao(const QVector<QVector<double>>& A, const QVector<QVector<double>>& B);
    QVector<QVector<double>> translacao(const QVector<QVector<double>> &matriz, const QVector<double> &valores);
    QVector<QVector<double>> rotacao(const QVector<QVector<double>> &matriz, double angulo);;
    QVector<QVector<double>> escalonar(double sx, double sy, const QVector<QVector<double>>& B);


};
#endif // MAINWINDOW_H
