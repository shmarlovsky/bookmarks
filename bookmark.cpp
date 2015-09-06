#include <QFile>
#include <QDebug>
#include "bookmark.h"
#include "ui_mainwindow.h"

unsigned int BookMark::serialNumber = 0;

BookMark::BookMark(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookMark)
{

    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::CustomizeWindowHint);

    ui->setupUi(this);

    qDebug() <<"SerialNumber: " <<serialNumber << endl;

    //create file name
    fileName = "/mnt/Data/.notes/";
    fileName.append(QString::number(serialNumber));
    fileName.append(".txt");

    qDebug() <<"fileName: " <<fileName << endl;

    loadTextfromFile();
    serialNumber++;

}


BookMark::~BookMark()
{
    serialNumber--;
    delete ui;
}


void BookMark::loadTextfromFile()
{

    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inStream(&file);
    ui->textEdit->setPlainText(inStream.readAll());
    //out << "\n";
    file.close();
}

void BookMark::createBookmark()
{
    emit createBookmarkRequest();
}

void BookMark::deleteBookmark()
{
    QFile file(fileName);
    file.remove();
    close();
    emit deleteBookmarkRequest(serialNumber);
}


void BookMark::saveToFile()
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream(&file);
    outStream << ui->textEdit->toPlainText();
    //out << "\n";
    file.close();
}


// hide to tray instead of to icon
void BookMark::changeEvent(QEvent *event)
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


