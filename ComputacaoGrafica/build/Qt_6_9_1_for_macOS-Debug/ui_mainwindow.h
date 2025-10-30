/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "teladedesenho.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    TelaDeDesenho *TelaDesenho;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *LabelComboBox;
    QComboBox *objectSelectorComboBox;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LabelComboBox_2;
    QDoubleSpinBox *translateXSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *LabelComboBox_3;
    QDoubleSpinBox *translateYSpinBox;
    QHBoxLayout *horizontalLayout_16;
    QLabel *LabelComboBox_7;
    QDoubleSpinBox *translateZSpinBox;
    QPushButton *translateButton;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *LabelComboBox_4;
    QDoubleSpinBox *escaleXSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *LabelComboBox_5;
    QDoubleSpinBox *escaleYSpinBox;
    QHBoxLayout *horizontalLayout_17;
    QLabel *LabelComboBox_9;
    QDoubleSpinBox *escaleZSpinBox;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *escaleButton;
    QPushButton *escaleEixoButton;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_3;
    QPushButton *rotateXButton;
    QPushButton *rotateYButton;
    QPushButton *rotateZButton;
    QHBoxLayout *horizontalLayout_9;
    QLabel *LabelComboBox_6;
    QSpinBox *rotationAngleSpinBox;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *panLeftButton;
    QVBoxLayout *verticalLayout_5;
    QPushButton *panUpButton;
    QPushButton *panDownButton;
    QPushButton *panRightButton;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *rotateRightButton;
    QPushButton *rotateLeftButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1494, 734);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        TelaDesenho = new TelaDeDesenho(centralwidget);
        TelaDesenho->setObjectName("TelaDesenho");
        TelaDesenho->setGeometry(QRect(60, 10, 971, 701));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(1151, 10, 336, 565));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        LabelComboBox = new QLabel(layoutWidget);
        LabelComboBox->setObjectName("LabelComboBox");

        horizontalLayout->addWidget(LabelComboBox);

        objectSelectorComboBox = new QComboBox(layoutWidget);
        objectSelectorComboBox->setObjectName("objectSelectorComboBox");

        horizontalLayout->addWidget(objectSelectorComboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        LabelComboBox_2 = new QLabel(layoutWidget);
        LabelComboBox_2->setObjectName("LabelComboBox_2");

        horizontalLayout_2->addWidget(LabelComboBox_2);

        translateXSpinBox = new QDoubleSpinBox(layoutWidget);
        translateXSpinBox->setObjectName("translateXSpinBox");
        translateXSpinBox->setMinimum(-99.989999999999995);

        horizontalLayout_2->addWidget(translateXSpinBox);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        LabelComboBox_3 = new QLabel(layoutWidget);
        LabelComboBox_3->setObjectName("LabelComboBox_3");

        horizontalLayout_3->addWidget(LabelComboBox_3);

        translateYSpinBox = new QDoubleSpinBox(layoutWidget);
        translateYSpinBox->setObjectName("translateYSpinBox");
        translateYSpinBox->setMinimum(-99.989999999999995);

        horizontalLayout_3->addWidget(translateYSpinBox);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        LabelComboBox_7 = new QLabel(layoutWidget);
        LabelComboBox_7->setObjectName("LabelComboBox_7");

        horizontalLayout_16->addWidget(LabelComboBox_7);

        translateZSpinBox = new QDoubleSpinBox(layoutWidget);
        translateZSpinBox->setObjectName("translateZSpinBox");
        translateZSpinBox->setMinimum(-99.989999999999995);

        horizontalLayout_16->addWidget(translateZSpinBox);


        verticalLayout->addLayout(horizontalLayout_16);

        translateButton = new QPushButton(layoutWidget);
        translateButton->setObjectName("translateButton");

        verticalLayout->addWidget(translateButton);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        LabelComboBox_4 = new QLabel(layoutWidget);
        LabelComboBox_4->setObjectName("LabelComboBox_4");

        horizontalLayout_5->addWidget(LabelComboBox_4);

        escaleXSpinBox = new QDoubleSpinBox(layoutWidget);
        escaleXSpinBox->setObjectName("escaleXSpinBox");
        escaleXSpinBox->setMinimum(0.000000000000000);

        horizontalLayout_5->addWidget(escaleXSpinBox);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        LabelComboBox_5 = new QLabel(layoutWidget);
        LabelComboBox_5->setObjectName("LabelComboBox_5");

        horizontalLayout_6->addWidget(LabelComboBox_5);

        escaleYSpinBox = new QDoubleSpinBox(layoutWidget);
        escaleYSpinBox->setObjectName("escaleYSpinBox");
        escaleYSpinBox->setMinimum(0.000000000000000);

        horizontalLayout_6->addWidget(escaleYSpinBox);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        LabelComboBox_9 = new QLabel(layoutWidget);
        LabelComboBox_9->setObjectName("LabelComboBox_9");

        horizontalLayout_17->addWidget(LabelComboBox_9);

        escaleZSpinBox = new QDoubleSpinBox(layoutWidget);
        escaleZSpinBox->setObjectName("escaleZSpinBox");
        escaleZSpinBox->setMinimum(0.000000000000000);

        horizontalLayout_17->addWidget(escaleZSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_17);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        escaleButton = new QPushButton(layoutWidget);
        escaleButton->setObjectName("escaleButton");

        horizontalLayout_8->addWidget(escaleButton);

        escaleEixoButton = new QPushButton(layoutWidget);
        escaleEixoButton->setObjectName("escaleEixoButton");

        horizontalLayout_8->addWidget(escaleEixoButton);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        rotateXButton = new QPushButton(layoutWidget);
        rotateXButton->setObjectName("rotateXButton");

        verticalLayout_3->addWidget(rotateXButton);

        rotateYButton = new QPushButton(layoutWidget);
        rotateYButton->setObjectName("rotateYButton");

        verticalLayout_3->addWidget(rotateYButton);

        rotateZButton = new QPushButton(layoutWidget);
        rotateZButton->setObjectName("rotateZButton");

        verticalLayout_3->addWidget(rotateZButton);


        horizontalLayout_10->addLayout(verticalLayout_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        LabelComboBox_6 = new QLabel(layoutWidget);
        LabelComboBox_6->setObjectName("LabelComboBox_6");

        horizontalLayout_9->addWidget(LabelComboBox_6);

        rotationAngleSpinBox = new QSpinBox(layoutWidget);
        rotationAngleSpinBox->setObjectName("rotationAngleSpinBox");
        rotationAngleSpinBox->setMinimum(-360);
        rotationAngleSpinBox->setMaximum(360);

        horizontalLayout_9->addWidget(rotationAngleSpinBox);


        horizontalLayout_10->addLayout(horizontalLayout_9);


        verticalLayout_4->addLayout(horizontalLayout_10);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout_6->addWidget(label);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        panLeftButton = new QPushButton(layoutWidget);
        panLeftButton->setObjectName("panLeftButton");

        horizontalLayout_11->addWidget(panLeftButton);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        panUpButton = new QPushButton(layoutWidget);
        panUpButton->setObjectName("panUpButton");

        verticalLayout_5->addWidget(panUpButton);

        panDownButton = new QPushButton(layoutWidget);
        panDownButton->setObjectName("panDownButton");

        verticalLayout_5->addWidget(panDownButton);


        horizontalLayout_11->addLayout(verticalLayout_5);

        panRightButton = new QPushButton(layoutWidget);
        panRightButton->setObjectName("panRightButton");

        horizontalLayout_11->addWidget(panRightButton);


        verticalLayout_6->addLayout(horizontalLayout_11);


        verticalLayout_7->addLayout(verticalLayout_6);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_13->addWidget(label_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        zoomInButton = new QPushButton(layoutWidget);
        zoomInButton->setObjectName("zoomInButton");

        horizontalLayout_12->addWidget(zoomInButton);

        zoomOutButton = new QPushButton(layoutWidget);
        zoomOutButton->setObjectName("zoomOutButton");

        horizontalLayout_12->addWidget(zoomOutButton);


        horizontalLayout_13->addLayout(horizontalLayout_12);


        verticalLayout_7->addLayout(horizontalLayout_13);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_15->addWidget(label_3);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        rotateRightButton = new QPushButton(layoutWidget);
        rotateRightButton->setObjectName("rotateRightButton");

        horizontalLayout_14->addWidget(rotateRightButton);

        rotateLeftButton = new QPushButton(layoutWidget);
        rotateLeftButton->setObjectName("rotateLeftButton");

        horizontalLayout_14->addWidget(rotateLeftButton);


        horizontalLayout_15->addLayout(horizontalLayout_14);


        verticalLayout_7->addLayout(horizontalLayout_15);


        verticalLayout_4->addLayout(verticalLayout_7);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        LabelComboBox->setText(QCoreApplication::translate("MainWindow", "Escolha o objeto que quer mudar", nullptr));
        LabelComboBox_2->setText(QCoreApplication::translate("MainWindow", "Transla\303\247\303\243o X", nullptr));
        LabelComboBox_3->setText(QCoreApplication::translate("MainWindow", "Transla\303\247\303\243o Y", nullptr));
        LabelComboBox_7->setText(QCoreApplication::translate("MainWindow", "Transla\303\247\303\243o Z", nullptr));
        translateButton->setText(QCoreApplication::translate("MainWindow", "Transladar na origem", nullptr));
        LabelComboBox_4->setText(QCoreApplication::translate("MainWindow", "Escala X", nullptr));
        LabelComboBox_5->setText(QCoreApplication::translate("MainWindow", "Escala Y", nullptr));
        LabelComboBox_9->setText(QCoreApplication::translate("MainWindow", "Escala Z", nullptr));
        escaleButton->setText(QCoreApplication::translate("MainWindow", "Escalonar na origem", nullptr));
        escaleEixoButton->setText(QCoreApplication::translate("MainWindow", "Escalonar no eixo", nullptr));
        rotateXButton->setText(QCoreApplication::translate("MainWindow", "Rotacionar em X", nullptr));
        rotateYButton->setText(QCoreApplication::translate("MainWindow", "Rotacionar em Y", nullptr));
        rotateZButton->setText(QCoreApplication::translate("MainWindow", "Rotacionar em Z", nullptr));
        LabelComboBox_6->setText(QCoreApplication::translate("MainWindow", "\303\202ngulo", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Navega\303\247\303\243o", nullptr));
        panLeftButton->setText(QCoreApplication::translate("MainWindow", "\342\227\200", nullptr));
        panUpButton->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        panDownButton->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        panRightButton->setText(QCoreApplication::translate("MainWindow", "\342\226\266", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Zoom", nullptr));
        zoomInButton->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        zoomOutButton->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Rota\303\247\303\243o", nullptr));
        rotateRightButton->setText(QCoreApplication::translate("MainWindow", "\342\206\273", nullptr));
        rotateLeftButton->setText(QCoreApplication::translate("MainWindow", "\342\206\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
