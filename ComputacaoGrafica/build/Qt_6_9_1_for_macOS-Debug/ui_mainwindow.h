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
#include <QtWidgets/QRadioButton>
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
    QVBoxLayout *verticalLayout_10;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_11;
    QWidget *layoutWidget2;
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
    QHBoxLayout *horizontalLayout_18;
    QVBoxLayout *verticalLayout_8;
    QLabel *LabelComboBox_4;
    QDoubleSpinBox *escaleXSpinBox;
    QVBoxLayout *verticalLayout_9;
    QLabel *LabelComboBox_5;
    QDoubleSpinBox *escaleYSpinBox;
    QVBoxLayout *verticalLayout_12;
    QLabel *LabelComboBox_9;
    QDoubleSpinBox *escaleZSpinBox;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *escaleButton;
    QPushButton *escaleEixoButton;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_13;
    QLabel *LabelComboBox_8;
    QSpinBox *rotationXSpinBox;
    QVBoxLayout *verticalLayout_14;
    QLabel *LabelComboBox_10;
    QSpinBox *rotationYSpinBox;
    QVBoxLayout *verticalLayout_15;
    QLabel *LabelComboBox_11;
    QSpinBox *rotationZSpinBox;
    QPushButton *rotationEixoButton;
    QLabel *label;
    QRadioButton *radioOrtogonal;
    QRadioButton *radioPerspectiva;
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
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_10 = new QVBoxLayout(layoutWidget);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_11 = new QVBoxLayout(layoutWidget1);
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(1140, 120, 312, 414));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        LabelComboBox = new QLabel(layoutWidget2);
        LabelComboBox->setObjectName("LabelComboBox");

        horizontalLayout->addWidget(LabelComboBox);

        objectSelectorComboBox = new QComboBox(layoutWidget2);
        objectSelectorComboBox->setObjectName("objectSelectorComboBox");

        horizontalLayout->addWidget(objectSelectorComboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        LabelComboBox_2 = new QLabel(layoutWidget2);
        LabelComboBox_2->setObjectName("LabelComboBox_2");

        horizontalLayout_2->addWidget(LabelComboBox_2);

        translateXSpinBox = new QDoubleSpinBox(layoutWidget2);
        translateXSpinBox->setObjectName("translateXSpinBox");
        translateXSpinBox->setMinimum(-99.989999999999995);

        horizontalLayout_2->addWidget(translateXSpinBox);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        LabelComboBox_3 = new QLabel(layoutWidget2);
        LabelComboBox_3->setObjectName("LabelComboBox_3");

        horizontalLayout_3->addWidget(LabelComboBox_3);

        translateYSpinBox = new QDoubleSpinBox(layoutWidget2);
        translateYSpinBox->setObjectName("translateYSpinBox");
        translateYSpinBox->setMinimum(-99.989999999999995);

        horizontalLayout_3->addWidget(translateYSpinBox);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        LabelComboBox_7 = new QLabel(layoutWidget2);
        LabelComboBox_7->setObjectName("LabelComboBox_7");

        horizontalLayout_16->addWidget(LabelComboBox_7);

        translateZSpinBox = new QDoubleSpinBox(layoutWidget2);
        translateZSpinBox->setObjectName("translateZSpinBox");
        translateZSpinBox->setMinimum(-99.989999999999995);

        horizontalLayout_16->addWidget(translateZSpinBox);


        verticalLayout->addLayout(horizontalLayout_16);

        translateButton = new QPushButton(layoutWidget2);
        translateButton->setObjectName("translateButton");

        verticalLayout->addWidget(translateButton);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        LabelComboBox_4 = new QLabel(layoutWidget2);
        LabelComboBox_4->setObjectName("LabelComboBox_4");

        verticalLayout_8->addWidget(LabelComboBox_4);

        escaleXSpinBox = new QDoubleSpinBox(layoutWidget2);
        escaleXSpinBox->setObjectName("escaleXSpinBox");
        escaleXSpinBox->setMinimum(0.000000000000000);

        verticalLayout_8->addWidget(escaleXSpinBox);


        horizontalLayout_18->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        LabelComboBox_5 = new QLabel(layoutWidget2);
        LabelComboBox_5->setObjectName("LabelComboBox_5");

        verticalLayout_9->addWidget(LabelComboBox_5);

        escaleYSpinBox = new QDoubleSpinBox(layoutWidget2);
        escaleYSpinBox->setObjectName("escaleYSpinBox");
        escaleYSpinBox->setMinimum(0.000000000000000);

        verticalLayout_9->addWidget(escaleYSpinBox);


        horizontalLayout_18->addLayout(verticalLayout_9);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");
        LabelComboBox_9 = new QLabel(layoutWidget2);
        LabelComboBox_9->setObjectName("LabelComboBox_9");

        verticalLayout_12->addWidget(LabelComboBox_9);

        escaleZSpinBox = new QDoubleSpinBox(layoutWidget2);
        escaleZSpinBox->setObjectName("escaleZSpinBox");
        escaleZSpinBox->setMinimum(0.000000000000000);

        verticalLayout_12->addWidget(escaleZSpinBox);


        horizontalLayout_18->addLayout(verticalLayout_12);


        verticalLayout_2->addLayout(horizontalLayout_18);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        escaleButton = new QPushButton(layoutWidget2);
        escaleButton->setObjectName("escaleButton");

        horizontalLayout_8->addWidget(escaleButton);

        escaleEixoButton = new QPushButton(layoutWidget2);
        escaleEixoButton->setObjectName("escaleEixoButton");

        horizontalLayout_8->addWidget(escaleEixoButton);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName("verticalLayout_13");
        LabelComboBox_8 = new QLabel(layoutWidget2);
        LabelComboBox_8->setObjectName("LabelComboBox_8");
        LabelComboBox_8->setMaximumSize(QSize(16777215, 50));

        verticalLayout_13->addWidget(LabelComboBox_8);

        rotationXSpinBox = new QSpinBox(layoutWidget2);
        rotationXSpinBox->setObjectName("rotationXSpinBox");
        rotationXSpinBox->setMinimum(-360);
        rotationXSpinBox->setMaximum(360);

        verticalLayout_13->addWidget(rotationXSpinBox);


        horizontalLayout_9->addLayout(verticalLayout_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName("verticalLayout_14");
        verticalLayout_14->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        LabelComboBox_10 = new QLabel(layoutWidget2);
        LabelComboBox_10->setObjectName("LabelComboBox_10");
        LabelComboBox_10->setMaximumSize(QSize(16777215, 50));

        verticalLayout_14->addWidget(LabelComboBox_10);

        rotationYSpinBox = new QSpinBox(layoutWidget2);
        rotationYSpinBox->setObjectName("rotationYSpinBox");
        rotationYSpinBox->setMinimum(-360);
        rotationYSpinBox->setMaximum(360);

        verticalLayout_14->addWidget(rotationYSpinBox);


        horizontalLayout_9->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName("verticalLayout_15");
        LabelComboBox_11 = new QLabel(layoutWidget2);
        LabelComboBox_11->setObjectName("LabelComboBox_11");
        LabelComboBox_11->setMaximumSize(QSize(16777215, 50));

        verticalLayout_15->addWidget(LabelComboBox_11);

        rotationZSpinBox = new QSpinBox(layoutWidget2);
        rotationZSpinBox->setObjectName("rotationZSpinBox");
        rotationZSpinBox->setMinimum(-360);
        rotationZSpinBox->setMaximum(360);

        verticalLayout_15->addWidget(rotationZSpinBox);


        horizontalLayout_9->addLayout(verticalLayout_15);


        verticalLayout_3->addLayout(horizontalLayout_9);

        rotationEixoButton = new QPushButton(layoutWidget2);
        rotationEixoButton->setObjectName("rotationEixoButton");

        verticalLayout_3->addWidget(rotationEixoButton);

        label = new QLabel(layoutWidget2);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        radioOrtogonal = new QRadioButton(layoutWidget2);
        radioOrtogonal->setObjectName("radioOrtogonal");
        radioOrtogonal->setChecked(true);

        verticalLayout_3->addWidget(radioOrtogonal);

        radioPerspectiva = new QRadioButton(layoutWidget2);
        radioPerspectiva->setObjectName("radioPerspectiva");
        radioPerspectiva->setChecked(false);

        verticalLayout_3->addWidget(radioPerspectiva);


        verticalLayout_4->addLayout(verticalLayout_3);

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
        LabelComboBox->setText(QCoreApplication::translate("MainWindow", "Objeto", nullptr));
        LabelComboBox_2->setText(QCoreApplication::translate("MainWindow", "Transla\303\247\303\243o X", nullptr));
        LabelComboBox_3->setText(QCoreApplication::translate("MainWindow", "Transla\303\247\303\243o Y", nullptr));
        LabelComboBox_7->setText(QCoreApplication::translate("MainWindow", "Transla\303\247\303\243o Z", nullptr));
        translateButton->setText(QCoreApplication::translate("MainWindow", "Transladar na origem", nullptr));
        LabelComboBox_4->setText(QCoreApplication::translate("MainWindow", "Escala X", nullptr));
        LabelComboBox_5->setText(QCoreApplication::translate("MainWindow", "Escala Y", nullptr));
        LabelComboBox_9->setText(QCoreApplication::translate("MainWindow", "Escala Z", nullptr));
        escaleButton->setText(QCoreApplication::translate("MainWindow", "Escalonar na origem", nullptr));
        escaleEixoButton->setText(QCoreApplication::translate("MainWindow", "Escalonar no eixo", nullptr));
        LabelComboBox_8->setText(QCoreApplication::translate("MainWindow", "Rotacionar X", nullptr));
        LabelComboBox_10->setText(QCoreApplication::translate("MainWindow", "Rotacionar Y", nullptr));
        LabelComboBox_11->setText(QCoreApplication::translate("MainWindow", "Rotacionar Z", nullptr));
        rotationEixoButton->setText(QCoreApplication::translate("MainWindow", "Rotacionar no eixo", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Proje\303\247\303\243o", nullptr));
        radioOrtogonal->setText(QCoreApplication::translate("MainWindow", "Ortogonal", nullptr));
        radioPerspectiva->setText(QCoreApplication::translate("MainWindow", "Perspectiva", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
