#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void refreshLayout(QGridLayout newlayout);

private:
    Ui::MainWindow *ui;
    QString os;
    int etape;
};

#endif // MAINWINDOW_H
