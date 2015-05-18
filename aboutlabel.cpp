#include "aboutlabel.h"

AboutLabel::AboutLabel()
{
    QPixmap logo(":/images/logo.png");
    this->setObjectName("aboutlabel");
    this->setPixmap(logo);
}

AboutLabel::~AboutLabel() {}

void AboutLabel::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    QMessageBox::information(this, "À propos...", "<h2>À propos de t411 Client Installer</h2>"
                                                  "Par Feeling97, avec l'aide de Goof, TuxAnge, et tous ceux qui ont aidé à tester pendant le développement!");
}

