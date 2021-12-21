#include "mainwindow.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("text.db");

    if(!db.open()){
        qDebug() << "open field" << db.lastError();
    }
    QString sqlCreate = QString("create table straff (id integer primary key, name varchar(10) not null,"
                             "age int not null);");
    QSqlQuery query;
    if(!query.exec(sqlCreate)){
        qDebug() << "field"<<db.lastError();
    }
}

MainWindow::~MainWindow()
{

}

