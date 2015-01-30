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

    this -> setTrayIconActions();
    this -> showTrayIcon();

    qDebug() <<"SerialNumber: " <<serialNumber << endl;

    fileName = "/mnt/Data/.notes/";
    fileName.append(QString::number(serialNumber));
    fileName.append(".txt");

    qDebug() <<"fileName: " <<fileName << endl;

    loadText();

    timer = new QTimer();
    timer->setInterval(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(saveToFile()));
    //timer->start();
}

// need to delete file if bookmark is deleted
MainWindow::~MainWindow()
{
    qDebug() << "DeKons!!!" << endl; 
    serialNumber--;

    delete ui;
}

void MainWindow::newWindow()
{
    MainWindow *newW = new MainWindow();
    newW->setAttribute(Qt::WA_DeleteOnClose);
    newW->show();
}

void MainWindow::loadText()
{

    QFile file(fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&file);
    ui->textEdit->setPlainText(in.readAll());
    //out << "\n";
    file.close();
}

// do saving with timer
void MainWindow::saveToFile()
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    //out << "\n";
    file.close();
}


//need move to dekons
void MainWindow::deleteBookMark()
{
    QFile file(fileName);
    file.remove();
    close();
}


//-------------------

void MainWindow::showTrayIcon()
{
    // Создаём экземпляр класса и задаём его свойства...
        MainWindow::trayIcon = new QSystemTrayIcon(this);
        QIcon trayImage(":/img/trayIcon.ico");
        trayIcon -> setIcon(trayImage);
        trayIcon -> setContextMenu(trayIconMenu);

        // Подключаем обработчик клика по иконке...
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

        // Выводим значок...
        trayIcon -> show();
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
        {
            case QSystemTrayIcon::Trigger:
            case QSystemTrayIcon::DoubleClick:
                this->showNormal();
                //this->trayActionExecute();
                break;
            default:
                break;
        }
}

// hide to tray instead of to icon
void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
        if (event -> type() == QEvent::WindowStateChange)
        {
            if (isMinimized())
            {
                this -> hide();
            }
        }
}

//void MainWindow::trayActionExecute()
//{
//    //QMessageBox::information(this, "TrayIcon", "Тестовое сообщение. Замените вызов этого сообщения своим кодом.");

//}

void MainWindow::setTrayIconActions()
{
    // Setting actions...
        minimizeAction = new QAction("Minimize", this);
        restoreAction = new QAction("Restore", this);
        newBookmarkAction = new QAction("New" ,this);
        quitAction = new QAction("Quit", this);


        // Connecting actions to slots...
        connect(newBookmarkAction, SIGNAL(triggered()), this, SLOT(newWindow()));
        connect (minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
        connect (restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
        connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        // Setting system tray's icon menu...
        trayIconMenu = new QMenu(this);
        trayIconMenu->setStyleSheet(NULL);
        trayIconMenu->addAction(newBookmarkAction);
        trayIconMenu -> addAction (minimizeAction);
        trayIconMenu -> addAction (restoreAction);
        trayIconMenu -> addAction (quitAction);
}







