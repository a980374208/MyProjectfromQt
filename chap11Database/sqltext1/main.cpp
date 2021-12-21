#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QStringList drivers = QSqlDatabase::drivers();
    qDebug()<<drivers;
    w.show();
    return a.exec();


}
