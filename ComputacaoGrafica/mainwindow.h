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

    // --- Slots de Transformação de Objeto (agora 3D) ---
    void on_translateButton_clicked();
    void on_rotationEixoButton_clicked();
    void on_escaleEixoButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<ObjetoVirtual> displayFile;
    int indiceDaWindow = -1;

    // Função de ajuda para carregar .obj
    ObjetoVirtual carregarObjetoOBJ(const QString& caminhoArquivo, const QString& nomeObjeto, QColor cor);

    // Função de ajuda para atualizar a UI
    void atualizarComboBoxDeObjetos();

    void ajustarWindowParaCena();
};
#endif // MAINWINDOW_H
