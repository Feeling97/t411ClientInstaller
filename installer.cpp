#include "installer.h"

Installer::Installer(MainWindow *argparent, QString argos) : QObject(argparent) {
    parent = argparent;
    os = argos;
    etape = 0;
}

Installer::~Installer() {}

QGridLayout* Installer::nextStage()
{
    etape++;
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(new QLabel("<h1>t411 Client Installer <small>v0.1</small></h1>"), 0, 0, 0, 0, Qt::AlignTop);
    QPixmap logo(":/images/logo.png");
    QLabel *logolabel = new QLabel;
    logolabel->setPixmap(logo);
    layout->addWidget(logolabel, 0, 0, 0, 0, Qt::AlignRight | Qt::AlignTop);

    if (etape == 1) { // Etape 1: Présentation
        layout->addWidget(new QLabel("Ce programme va installer " + client + " pour " + os + " avec la configuration recommandée pour <a href=\"http://www.t411.io/\">t411.io</a><br /><br />\
        Configuration recommandée :\
        <ul>\
            <li>Port 50500</li>\
            <li>DHT/Recherche locale de pairs desactivé</li>\
            <li>Mises à jour automatiques désactivées</li>\
            <li>Aucune limite d'envoi et de réception</li>\
            <li>Pré-allocation de l'espace disque pour les nouveaux fichiers</li>\
            <li>Cryptage des échanges forcé</li>\
        </ul>\
        "), 0, 0, 0, 0);
        parent->enableNext();
    }
    else if (etape == 2) { // Etape 2: Téléchargement
        QVBoxLayout *centerlayout = new QVBoxLayout();
        centerlayout->addWidget(new QLabel("Téléchargement de " + client + "..."));
        QProgressBar *dbar = new QProgressBar();
        centerlayout->addWidget(dbar);
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignCenter);

    }
    else if (etape == 3) { // Etape 3: Installation du client
        layout->addWidget(new QLabel("Installation du client (à coder)"), 0, 0, 0, 0);
        parent->enableNext();
    }
    else if (etape == 4) { // Etape 4: Installation de la config
        layout->addWidget(new QLabel("Installation de la config (à coder)"), 0, 0, 0, 0);
        parent->enableNext();
    }
    else if (etape == 5) { // Etape 5: Fin
        layout->addWidget(new QLabel("Fin (à coder)"), 0, 0, 0, 0);
    }

    return layout;
}

void Installer::determineClient()
{
#if defined(Q_OS_WIN) // Windows
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
        QMessageBox::critical(0, "Erreur", "Impossible de déterminer le client correspondant à votre système<br />Vous pouvez utiliser le checker en ligne :<br /><a href='http://irc.t411.io/checker/'>Cliquez ici</a>");
        exit(1);
    }
#else // Linux et Mac
    client = "Transmission 2.84";
#endif
}

void Installer::saveDownloadedFile()
{

}
