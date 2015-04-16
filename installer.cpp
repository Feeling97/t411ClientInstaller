#include "installer.h"

QGridLayout* nextStage(QString client, QString os, int etape)
{
    QGridLayout *layout = new QGridLayout();
    if (etape == 0) { // Etape 1: Présentation
        layout->addWidget(new QLabel("Ce programme va installer " + client + " pour " + os + " avec la configuration recommandée"), 0, 0);
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
