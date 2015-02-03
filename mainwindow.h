#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   QPushButton *getNewButton();
   QPushButton *getDeleteButton();

private:
    Ui::MainWindow *ui;
    static unsigned int serialNumber;
    QString fileName;
    void loadTextfromFile();

public slots:
    void changeEvent(QEvent*);
    void saveToFile();
    void deleteBookMark();

signals:
   void windowClosed();
};



#endif // MAINWINDOW_H
