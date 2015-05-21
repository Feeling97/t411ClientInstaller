#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Détection du Windows
    QString os;
    if (QSysInfo::windowsVersion() == QSysInfo::WV_NT)
        os = "Windows NT";
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_2000)
        os = "Windows 2000";
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_XP)
        os = "Windows XP";
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_2003)
        os = "Windows XP x64";
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_VISTA)
        os = "Windows Vista";
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS7)
        os = "Windows 7";
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS8)
        os = "Windows 8";
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS8_1)
        os = "Windows 8.1";
    else
        os = "Windows";

    installer = new Installer(this, os);

    connect(installer, SIGNAL(refreshLayout(QGridLayout*)), this, SLOT(refreshLayout(QGridLayout*)));

    installer->determineClient();
    installer->doNextStage();
}

MainWindow::~MainWindow()
{
    clear();
    delete ui;
    delete installer;
}

void MainWindow::refreshLayout(QGridLayout *newlayout)
{
    clear();
    ui->o_content->setLayout(newlayout);
}

void MainWindow::pressedQuit()
{
    QMessageBox wannaQuit(QMessageBox::Question, "Quitter", "Voulez-vous vraiment quitter l'installation ?", QMessageBox::Yes | QMessageBox::No);
    wannaQuit.setButtonText(QMessageBox::Yes, "Oui");
    wannaQuit.setButtonText(QMessageBox::No, "Non");
    wannaQuit.setDefaultButton(QMessageBox::No);

    if (wannaQuit.exec() == QMessageBox::Yes)
        qApp->quit();
}

void MainWindow::pressedNext()
{
    ui->b_suivant->setDisabled(true);
    installer->doNextStage();
}

void MainWindow::enableNext()
{
    ui->b_suivant->setEnabled(true);
}

void MainWindow::disableQuit()
{
    ui->b_quitter->setDisabled(true);
}

void MainWindow::enableFinish()
{
    ui->b_suivant->setText("Terminer");
    ui->b_suivant->setEnabled(true);
    ui->b_suivant->disconnect();
    connect(ui->b_suivant, SIGNAL(released()), installer, SLOT(pressedFinish()));
}

void MainWindow::clear()
{
    foreach (QWidget *w, ui->o_content->findChildren<QWidget*>())
        if (w->objectName() != "t411label" && w->objectName() != "aboutlabel")
            w->deleteLater();
    delete ui->o_content->layout();
}
