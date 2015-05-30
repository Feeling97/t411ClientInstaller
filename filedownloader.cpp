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

#include "filedownloader.h"

FileDownloader::FileDownloader() {}

FileDownloader::FileDownloader(QUrl imageUrl, Installer *parent) : QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
}

FileDownloader::~FileDownloader() { }

bool FileDownloader::isConnected() const
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    bool result = false;

    for (int i = 0; i < ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);
        if (iface.flags().testFlag(QNetworkInterface::IsUp) && !iface.flags().testFlag(QNetworkInterface::IsLoopBack) )
        {
            for (int j = 0; j<iface.addressEntries().count(); j++)
            {
                result = true;
            }
        }
    }

    if (result)
    {
        if (QProcess::execute("ping", QStringList() << "-n" << "1" << "www.google.fr") == 0)
            return true;
    }

    return false;
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    pReply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const
{
    return m_DownloadedData;
}
