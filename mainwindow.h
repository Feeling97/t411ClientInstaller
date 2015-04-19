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

    void refreshLayout(QGridLayout *newlayout);

public slots:
    void pressedNext();
    void enableNext();

private:
    Ui::MainWindow *ui;
    Installer *installer;
};

#endif // MAINWINDOW_H
