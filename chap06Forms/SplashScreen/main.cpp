#include "mainwindow.h"
#include "dlglogin.h"
#include <QTextCodec>

#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec); //解决汉字乱码问题
    QApplication a(argc, argv);
    DlgLogin *dlg = new DlgLogin;

    if(dlg->exec() == QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();

    }else
        return  0;

}
