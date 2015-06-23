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

#include "aboutlabel.h"

AboutLabel::AboutLabel()
{
    QPixmap logo(":/images/logo.png");
    this->setObjectName("aboutlabel");
    this->setPixmap(logo);
    about = new QMessageBox(QMessageBox::Information, "À propos...", "<h2>À propos de t411 Client Installer</h2>"
                                                                     "<p align=\"justify\">Par Feeling, avec l'aide de tous ceux qui ont aidé à tester<br />"
                                                                     "Et des grands remerciements tout particulièrement à Goof, TuxAnge, et Nic0patch<br />"
                                                                     "qui m'ont énormément aidé !</p>",
                                                                     QMessageBox::Ok);
}

AboutLabel::~AboutLabel() {}

void AboutLabel::enterEvent(QEvent *event)
{
    qApp->setOverrideCursor(Qt::PointingHandCursor);
    event->accept();
}

void AboutLabel::leaveEvent(QEvent *event)
{
    qApp->restoreOverrideCursor();
    event->accept();
}

void AboutLabel::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    about->exec();
}

