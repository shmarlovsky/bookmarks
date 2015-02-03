#include <QApplication>
#include <QDebug>
#include "tray.h"

int Tray::windowCount = 0;

Tray::Tray()
{
    //creating actions for menu
    minimizeAction = new QAction("Minimize", this);
    restoreAction = new QAction("Restore", this);
    createBookmarkAction = new QAction("New" ,this);
    quitAction = new QAction("Quit", this);

    // Setting system tray's icon menu
    trayIconMenu = new QMenu();
    trayIconMenu->setStyleSheet("background: gray");
    trayIconMenu->addAction(createBookmarkAction);
    trayIconMenu->addAction (minimizeAction);
    trayIconMenu->addAction (restoreAction);
    trayIconMenu->addAction (quitAction);

    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/img/trayIcon.ico");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(trayIconMenu);
    trayIcon -> show();

    createBookMark();

    // Connecting actions to slots
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    connect(createBookmarkAction, SIGNAL(triggered()), this, SLOT(createBookMark()));
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hideAll()));
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showAll()));
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

Tray::~Tray()
{

}

void Tray::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{

    switch (reason)
        {
            //case QSystemTrayIcon::Trigger:
            case QSystemTrayIcon::DoubleClick:
                this->showAll();
                break;
            default:
                break;
        }
}


void Tray::createBookMark()
{
    if(windowCount<MAX)
    {
        books[windowCount] = new MainWindow();
        connect(books[windowCount]->getNewButton(), SIGNAL(clicked()), this, SLOT(createBookMark()));
        connect(books[windowCount], SIGNAL(windowClosed()), this, SLOT(windowClosed()));
        //connect(books[windowCount]->getDeleteButton(), SIGNAL(clicked()), this, SLOT(deleteBookMark()));
        if(windowCount>0)
        {
            books[windowCount]->setAttribute(Qt::WA_DeleteOnClose);
        }
        books[windowCount]->show();
        windowCount++;
        qDebug() << "WindowCount (after incr.): " << windowCount << endl;
    }
}

void Tray::hideAll()
{
    for (int i=0; i<windowCount; i++)
    {
        books[i]->hide();
        //books[i]->showMinimized();

    }
}

void Tray::showAll()
{
    for (int i=0; i<windowCount; i++)
    {
        books[i]->show();
    }
}

void Tray::windowClosed()
{
    windowCount--;
    qDebug() << "WindowCount: " << windowCount << endl;
}




