#include "options.h"

Options::Options(Installer *arg_parent) : QDialog(arg_parent->getParent(), Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    parent = arg_parent;
    QVBoxLayout *layout = new QVBoxLayout;
    QGridLayout *contentLayout = new QGridLayout;
    contentBox = new QGroupBox("Options", this);
    portLine = new QLineEdit;
    portLine->setInputMask("00000");
    portLine->setMaxLength(5);
    portLine->setFixedSize(40, portLine->sizeHint().height());
    portLine->setText(parent->getOption("port"));
    contentLayout->addWidget(new QLabel("Port :"), 0, 0);
    contentLayout->addWidget(portLine, 0, 1);
    fileLine = new QLineEdit;
    fileLine->setText(parent->getOption("files"));
    contentLayout->addWidget(new QLabel("Fichiers téléchargés :"), 1, 0);
    contentLayout->addWidget(fileLine, 1, 1);
    torrentLine = new QLineEdit;
    torrentLine->setText(parent->getOption("torrents"));
    contentLayout->addWidget(new QLabel("Fichiers .torrent :"), 2, 0);
    contentLayout->addWidget(torrentLine, 2, 1);
    contentBox->setLayout(contentLayout);
    layout->addWidget(contentBox);
    QPushButton *ok = new QPushButton("OK");
    ok->setFixedSize(80, ok->sizeHint().height());
    layout->addWidget(ok);
    layout->setAlignment(ok, Qt::AlignRight);
    this->setLayout(layout);
    this->setFixedSize(400, 180);

    ClickEater *clickEater = new ClickEater;
    fileLine->installEventFilter(clickEater);
    torrentLine->installEventFilter(clickEater);

    connect(ok, SIGNAL(released()), this, SLOT(close()));

    connect(portLine, SIGNAL(textEdited(QString)), this, SLOT(valueChanged(QString)));
    connect(fileLine, SIGNAL(textEdited(QString)), this, SLOT(valueChanged(QString)));
    connect(torrentLine, SIGNAL(textEdited(QString)), this, SLOT(valueChanged(QString)));
}

Options::~Options() {}

void Options::open()
{
    this->show();
}

void Options::valueChanged(QString text)
{
    QString name;
    if (portLine->isModified())
    {
        portLine->setModified(false);
        name = "port";
    }
    else if (fileLine->isModified())
    {
        fileLine->setModified(false);
        name = "files";
    }
    else
    {
        torrentLine->setModified(false);
        name = "torrents";
    }

    parent->setOption(name, text);
}

void Options::closeEvent(QCloseEvent *event)
{
    if (portLine->text().isEmpty() || portLine->text().toInt() <= 1 || torrentLine->text().isEmpty() || fileLine->text().isEmpty())
    {
        QMessageBox::information(this, "Options", "Vous n'avez pas rempli correctement un ou plusieurs champs");
        event->ignore();
        return;
    }

    event->accept();
}
