#include <QFile>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

unsigned int MainWindow::serialNumber = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qDebug() << "Kons!!!" << endl;
    serialNumber++;
    ui->setupUi(this);

    qDebug() <<"SerialNumber: " <<serialNumber << endl;

    //create file name
    fileName = "/mnt/Data/.notes/";
    fileName.append(QString::number(serialNumber));
    fileName.append(".txt");

    qDebug() <<"fileName: " <<fileName << endl;

    loadTextfromFile();

}


MainWindow::~MainWindow()
{
    qDebug() << "DeKons!!!" << endl; 
    serialNumber--;
    delete ui;
    emit windowClosed();
}


void MainWindow::loadTextfromFile()
{

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inStream(&file);
    ui->textEdit->setPlainText(inStream.readAll());
    //out << "\n";
    file.close();
}


void MainWindow::saveToFile()
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream(&file);
    outStream << ui->textEdit->toPlainText();
    //out << "\n";
    file.close();
}


void MainWindow::deleteBookMark()
{
    QFile file(fileName);
    file.remove();
    close();
}

QPushButton *MainWindow::getNewButton()
{
    return this->ui->newButton;
}

QPushButton *MainWindow::getDeleteButton()
{
    return this->ui->deleteButton;
}

// hide to tray instead of to icon
void MainWindow::changeEvent(QEvent *event)
{
        //QMainWindow::changeEvent(event);
        if (event -> type() == QEvent::WindowStateChange)
        {
            if (isMinimized())
            {
                hide();
            }
        }

}


