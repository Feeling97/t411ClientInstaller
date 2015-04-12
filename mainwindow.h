#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void refreshLayout(QGridLayout *newlayout);
    void nextStage();
    void determineClient();

private:
    Ui::MainWindow *ui;
    QString os, client;
    int etape;
};

#endif // MAINWINDOW_H
