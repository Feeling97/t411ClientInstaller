#include "installer.h"

QGridLayout* nextStage(MainWindow *parent, QString client, QString os, int *etape)
{
    *etape = *etape + 1;
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(new QLabel("<h1>t411 Client Installer <small>v0.0.5</small></h1>"), 0, 0, 0, 0, Qt::AlignTop);
    if (*etape == 1) { // Etape 1: Présentation
        layout->addWidget(new QLabel("Ce programme va installer " + client + " pour " + os + " avec la configuration recommandée"), 0, 0, 0, 0);
    }
    else if (*etape == 2) { // Etape 2: Téléchargement
        layout->addWidget(new QLabel("Téléchargement (à coder)"), 0, 0, 0, 0);
    }
    else if (*etape == 3) { // Etape 3: Installation du client
        layout->addWidget(new QLabel("Installation du client (à coder)"), 0, 0, 0, 0);
    }
    else if (*etape == 4) { // Etape 4: Installation de la config
        layout->addWidget(new QLabel("Installation de la config (à coder)"), 0, 0, 0, 0);
    }
    else if (*etape == 5) { // Etape 5: Fin
        layout->addWidget(new QLabel("Fin (à coder)"), 0, 0, 0, 0);
        parent->disableSuivant();
    }

    return layout;
}

QString determineClient(QString os)
{
#if defined(Q_OS_WIN) // Windows
    if (os == "Windows 8.1")
        return "qBittorrent";
    else if (os == "Windows 8")
        return "qBittorrent";
    else if (os == "Windows 7")
        return "µTorrent 2.2.1";
    else if (os == "Windows Vista")
        return "µTorrent 2.2.1";
    else if (os == "Windows XP x64")
        return "µTorrent 2.2.1";
    else if (os == "Windows XP")
        return "µTorrent 2.2.1";
    else if (os == "Windows 2000")
        return "µTorrent 2.2.1";
    else if (os == "Windows NT")
        return "µTorrent 2.2.1";
    else
    {
        QMessageBox::critical(0, "Erreur", "Impossible de déterminer le client correspondant à votre système<br />Vous pouvez utiliser le checker en ligne :<br /><a href='http://irc.t411.io/checker/'>Cliquez ici</a>");
        exit(1);
    }
#else // Linux et Mac
    return "Transmission 2.84";
#endif
}
