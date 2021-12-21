#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QFileDialog>
void MainWindow::on_actOpen_IODevice_triggered()
{
    QString filter = "头文件(*.h);;cpp(*.cpp);;文本(*.txt);;所有(*.*)";
    QString fileName = QFileDialog::getOpenFileName(this,"打开一个文件",
                                                    QCoreApplication::applicationDirPath(),filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        ui->plainTextEdit->setPlainText(
                    QString::fromLocal8Bit(file.readAll()));
        file.close();
        ui->tabWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_actSave_IODevice_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "保持文件";
    QString filter = "头文件(*.h);;cpp(*.cpp);;文本(*.txt);;所有(*.*)";
    QString fileName = QFileDialog::getSaveFileName(this,title,curPath,filter);
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QString str = ui->plainTextEdit->toPlainText();
        QByteArray bytearray = str.toUtf8();
        file.write(bytearray,bytearray.length());
        ui->tabWidget->setCurrentIndex(0);
    }


}

#include <QTextStream>
void MainWindow::on_actOpen_TextStream_triggered()
{
    QString filter = "头文件(*.h);;cpp(*.cpp);;文本(*.txt);;所有(*.*)";
    QString fileName = QFileDialog::getOpenFileName(this,"打开一个文件",
                                                    QCoreApplication::applicationDirPath(),filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&file);
        stream.setAutoDetectUnicode(true);
//        ui->plainTextEdit_2->setPlainText(stream.readAll());
        while(!stream.atEnd()){
            ui->plainTextEdit_2->appendPlainText(stream.readLine());
        }
        file.close();
        ui->tabWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_actSave_TextStream_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "保持文件";
    QString filter = "头文件(*.h);;cpp(*.cpp);;文本(*.txt);;所有(*.*)";
    QString fileName = QFileDialog::getSaveFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QTextStream stream(&file);
        stream.setAutoDetectUnicode(true);

        QString str = ui->plainTextEdit_2->toPlainText();
        stream<<str;
        ui->tabWidget->setCurrentIndex(1);
    }

}

