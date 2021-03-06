/*  This file is part of t411 Client Installer.

    t411 Client Installer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    t411 Client Installer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with t411 Client Installer.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QApplication>

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
        QObject::connect(b_quitter, SIGNAL(released()), MainWindow, SLOT(pressedQuit()));
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
