/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QFrame>
#include <QGridLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *b_quitter;
    QPushButton *b_suivant;
    QFrame *line;
    QWidget *o_content;

    void setupUi(QDialog *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString("MainWindow"));
        MainWindow->setFixedSize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(MainWindow);
        gridLayoutWidget->setObjectName(QString("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 360, 581, 25));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        b_quitter = new QPushButton(gridLayoutWidget);
        b_quitter->setObjectName(QString("b_quitter"));
        b_quitter->setDefault(false);
        b_quitter->setFlat(false);

        gridLayout->addWidget(b_quitter, 0, 0, 1, 1, Qt::AlignLeft);

        b_suivant = new QPushButton(gridLayoutWidget);
        b_suivant->setObjectName(QString("b_suivant"));

        gridLayout->addWidget(b_suivant, 0, 1, 1, 1, Qt::AlignRight);

        line = new QFrame(MainWindow);
        line->setObjectName(QString("line"));
        line->setGeometry(QRect(10, 350, 581, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        o_content = new QWidget(MainWindow);
        o_content->setObjectName(QString("o_content"));
        o_content->setGeometry(QRect(10, 10, 581, 341));
        o_content->setAutoFillBackground(false);
        QWidget::setTabOrder(b_suivant, b_quitter);

        retranslateUi(MainWindow);
        QObject::connect(b_quitter, SIGNAL(released()), MainWindow, SLOT(close()));
        QObject::connect(b_suivant, SIGNAL(released()), MainWindow, SLOT(pressedNext()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QDialog *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "t411 Client Installer", 0));
        b_quitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        b_suivant->setText(QApplication::translate("MainWindow", "Suivant", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
