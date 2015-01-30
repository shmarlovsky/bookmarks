#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //load text from txt file
    void loadText();
private slots:
    void newWindow();
    void saveToFile();
    void deleteBookMark();

    //tray icon
    void changeEvent(QEvent*);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    //void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();


private:
    Ui::MainWindow *ui;
    static unsigned int serialNumber;
    QString fileName;
    QTimer *timer;

    //tray icon
    QMenu *trayIconMenu;
    QAction *newBookmarkAction;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;

};



#endif // MAINWINDOW_H
