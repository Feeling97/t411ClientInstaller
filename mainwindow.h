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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QLabel>
#include "installer.h"

namespace Ui {
class MainWindow;
}

class Installer;
class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void enableNext();
    void disableQuit();
    void enableFinish();

public slots:
    void refreshLayout(QGridLayout *newlayout);
    void pressedNext();
    void pressedQuit();

private:
    void clear();

private:
    Ui::MainWindow *ui;
    Installer *installer;
};

#endif // MAINWINDOW_H
