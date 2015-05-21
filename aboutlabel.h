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

#ifndef ABOUTLABEL_H
#define ABOUTLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>

class AboutLabel : public QLabel
{
    Q_OBJECT

public:
    explicit AboutLabel();
    ~AboutLabel();

public slots:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // ABOUTLABEL_H
