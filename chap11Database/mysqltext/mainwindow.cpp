#include "mainwindow.h"
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QStringList drivers = QSqlDatabase::drivers();
    qDebug()<<drivers;
    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("localhost");
    db.setDatabaseName("myemployees");
//    db.setUserName("root");
//    db.setPassword("lovebin.1");

    if(!db.open()){
        qDebug()<<"open field"<<db.lastError();
    }
}

MainWindow::~MainWindow()
{
}

