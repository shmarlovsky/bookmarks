#include <QApplication>
#include <QDebug>
#include "tray.h"

int Tray::bookmarkCount = 0;
//int Tray::MAX = 10;

Tray::Tray()
{
    //creating actions for menu
    minimizeAction = new QAction("Minimize", this);
    restoreAction = new QAction("Restore", this);
    createBookmarkAction = new QAction("New" ,this);
    quitAction = new QAction("Quit", this);

    // Setting system tray's icon menu
    trayIconMenu = new QMenu();
    //trayIconMenu->setStyleSheet("background: gray");
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
    //booksList.push_back(new BookMark());
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
//    if(bookmarkCount<MAX)
//    {
//        books[bookmarkCount] = new BookMark();
//       // connect(books[bookmarkCount], SIGNAL(createBookmarkRequest()), this, SLOT(createBookMark()));
//        connect(books[bookmarkCount], SIGNAL(createBookmarkRequest()),this, SLOT(createBookMark()));
//         connect(books[bookmarkCount], SIGNAL(deleteBookmarkRequest(int)),this, SLOT(deleteBookMark(int)));
//        if(bookmarkCount>0)
//        {
//            books[bookmarkCount]->setAttribute(Qt::WA_DeleteOnClose);
//        }
//        books[bookmarkCount]->show();
//        bookmarkCount++;
//        qDebug() << "WindowCount (after incr.): " << bookmarkCount << endl;
//    }

    if(bookmarkCount<MAX)
    {
        booksList.push_back(new BookMark());
        connect(booksList.back(), SIGNAL(createBookmarkRequest()),this, SLOT(createBookMark()));
        connect(booksList.back(), SIGNAL(deleteBookmarkRequest(int)),this, SLOT(deleteBookMark(int)));
        if(bookmarkCount>0)
        {
            booksList.back()->setAttribute(Qt::WA_DeleteOnClose);
        }
        booksList.back()->show();
        bookmarkCount++;
        qDebug() << "WindowCount (after incr.): " << bookmarkCount << endl;
    }
}

void Tray::hideAll()
{
    for (int i=0; i<bookmarkCount; i++)
    {
        books[i]->hide();
        //books[i]->showMinimized();

    }
}

void Tray::showAll()
{
    for (int i=0; i<bookmarkCount; i++)
    {
        books[i]->show();
    }
}

void Tray::deleteBookMark(int number)
{
      //std::vector<BookMark>::iterator iter = booksList.at(0);
//    booksList.erase(iter);
//    bookmarkCount--;
//    booksList.resize(bookmarkCount);
    bookmarkCount--;
    qDebug() << "WindowCount: " << bookmarkCount << endl;
}

