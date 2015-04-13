#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Détection approfondie de l'OS
    #if defined(Q_OS_WIN) // Windows
    if (QSysInfo::windowsVersion() == QSysInfo::WV_NT) {
        os = "Windows NT";
    }
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_2000) {
        os = "Windows 2000";
    }
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_XP) {
        os = "Windows XP";
    }
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_2003) {
        os = "Windows XP x64";
    }
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_VISTA) {
        os = "Windows Vista";
    }
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS7) {
        os = "Windows 7";
    }
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS8) {
        os = "Windows 8";
    }
    else if (QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS8_1) {
        os = "Windows 8.1";
    }
    else {
        os = "Windows";
    }
    #elif defined(Q_OS_MAC) // Mac
    os = "Mac OS X";
    #elif defined(Q_OS_LINUX) // Linux
    os = "Linux";
    #else // Autres systèmes
    os = "Inconnu";
    QMessageBox::critical(this, "Erreur", "Votre système d'exploitation n'est pas supporté<br /><a href='http://irc.t411.io/checker/'>Checker en ligne</a>");
    this->close();
    #endif

    etape = 0;
    determineClient();
    nextStage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshLayout(QGridLayout *newlayout)
{
    ui->o_content->setLayout(newlayout);
}

void MainWindow::nextStage()
{
    etape++;
    QGridLayout *layout = new QGridLayout();
    if (etape == 1) { // Etape 1: Présentation
        layout->addWidget(new QLabel("Ce programme va installer " + client + " pour " + os + " avec la configuration recommandée"), 0, 0);
        refreshLayout(layout);
    }
}

void MainWindow::determineClient()
{
    if (os == "Windows 8.1")
        client = "qBittorrent";
    else if (os == "Windows 8")
        client = "qBittorrent";
    else if (os == "Windows 7")
        client = "µTorrent 2.2.1";
    else if (os == "Windows Vista")
        client = "µTorrent 2.2.1";
    else if (os == "Windows XP x64")
        client = "µTorrent 2.2.1";
    else if (os == "Windows XP")
        client = "µTorrent 2.2.1";
    else if (os == "Windows 2000")
        client = "µTorrent 2.2.1";
    else if (os == "Windows NT")
        client = "µTorrent 2.2.1";
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible de déterminer le client correspondant à votre système<br />Vous pouvez utiliser le checker en ligne :<br /><a href='http://irc.t411.io/checker/'>Cliquez ici</a>");
        this->close();
    }
}
