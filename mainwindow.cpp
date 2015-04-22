#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Détection approfondie de l'OS
    QString os;
    #if defined(Q_OS_WIN) // Windows
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
    #elif defined(Q_OS_MAC) // Mac
    os = "Mac OS X";
    #elif defined(Q_OS_LINUX) // Linux
    os = "Linux";
    #else // Autres systèmes
    os = "Inconnu";
    QMessageBox::critical(this, "Erreur", "Votre système d'exploitation n'est pas supporté<br /><a href='http://irc.t411.io/checker/'>Checker en ligne</a>");
    exit(1);
    #endif

    installer = new Installer(this, os);

    installer->determineClient();
    ui->o_content->setLayout(installer->nextStage());
}

MainWindow::~MainWindow()
{
    foreach (QWidget *w, ui->o_content->findChildren<QWidget*>()) delete w;
    delete ui->o_content->layout();
    delete ui;
}

void MainWindow::refreshLayout(QGridLayout *newlayout)
{
    foreach (QWidget *w, ui->o_content->findChildren<QWidget*>()) delete w;
    delete ui->o_content->layout();
    ui->o_content->setLayout(newlayout);
}

void MainWindow::pressedNext()
{
    ui->b_suivant->setDisabled(true);
    refreshLayout(installer->nextStage());
}

void MainWindow::enableNext()
{
    ui->b_suivant->setEnabled(true);
}

void MainWindow::disableNext()
{
    ui->b_suivant->hide();
}
