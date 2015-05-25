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
                                                                     "Par Feeling97, avec l'aide de Goof, TuxAnge, et tous ceux qui ont aidé à tester pendant le développement!",
                                                                     QMessageBox::Ok);
}

AboutLabel::~AboutLabel() {}

void AboutLabel::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    about->exec();
}

