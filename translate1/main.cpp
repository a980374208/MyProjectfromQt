#include "mainwindow.h"
#include "QTranslator"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTranslator* pTranslate = new QTranslator;
    pTranslate->load("language.zh_CN.qm");
    a.installTranslator(pTranslate);
    w.show();
    return a.exec();
}
