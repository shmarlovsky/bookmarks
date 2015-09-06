#ifndef TRAY_H
#define TRAY_H
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "bookmark.h"


const int MAX = 10;
class BookMark;
class Tray: public QObject
{
    Q_OBJECT
public:
    Tray();
    ~Tray();

public slots:
    void createBookMark();
    void deleteBookMark(int number);
    void hideAll();
    void showAll();

   // void windowClosed();


private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);


private:
    //menu
    QMenu *trayIconMenu;
    QAction *createBookmarkAction;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;

    static int bookmarkCount;
    // max number of bookmarks

    BookMark* books[MAX];
    std::vector <BookMark*> booksList;

};



#endif // TRAY_H
