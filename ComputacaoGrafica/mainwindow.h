#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objetovirtual.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // --- Slots de Navegação da Câmera ---
    void on_panUpButton_clicked();
    void on_panDownButton_clicked();
    void on_panLeftButton_clicked();
    void on_panRightButton_clicked();
    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
    void on_rotateLeftButton_clicked();
    void on_rotateRightButton_clicked();

    // --- Slots de Transformação de Objeto (agora 3D) ---
    void on_translateButton_clicked();
    void on_rotationEixoButton_clicked();
    void on_escaleEixoButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<ObjetoVirtual> displayFile;

    // Função de ajuda para carregar .obj
    ObjetoVirtual carregarObjetoOBJ(const QString& caminhoArquivo, const QString& nomeObjeto, QColor cor);

    // Função de ajuda para atualizar a UI
    void atualizarComboBoxDeObjetos();
};
#endif // MAINWINDOW_H
