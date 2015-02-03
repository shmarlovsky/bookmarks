#ifndef TRAY_H
#define TRAY_H
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>

#include "mainwindow.h"


const int MAX = 10;
class MainWindow;
class Tray: public QObject
{
    Q_OBJECT
public:
    Tray();
    ~Tray();

public slots:
    void createBookMark();
    void hideAll();
    void showAll();
    void windowClosed();

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);


private:
    QMenu *trayIconMenu;
    QAction *createBookmarkAction;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    MainWindow* books[MAX];
    static int windowCount;

};



#endif // TRAY_H
