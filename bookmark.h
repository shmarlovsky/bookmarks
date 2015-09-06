#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class BookMark;
}

class BookMark : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookMark(QWidget *parent = 0);
    ~BookMark();


private:
    Ui::BookMark *ui;
    static unsigned int serialNumber;
    QString fileName;
    void loadTextfromFile();

private slots:
    void createBookmark();
    void deleteBookmark();

public slots:
    void changeEvent(QEvent*);
    void saveToFile();


signals:
   void windowClosed();
   void createBookmarkRequest();
   void deleteBookmarkRequest(int);
};



#endif // MAINWINDOW_H
