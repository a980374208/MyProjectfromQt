#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nam = new QNetworkAccessManager(this);
    connect(nam,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(finishedSlot(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete nam;
}


void MainWindow::on_pushButton_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl(ui->lineEdit->text()));
    QByteArray postData;
    //postData.append()
    QNetworkReply* reply = nam->get(request);



}

void MainWindow::finishedSlot(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError){
        QByteArray bytes = reply->readAll();
        qDebug()<<bytes;
        QString string = QString::fromUtf8(bytes);
        ui->textBrowser->setText(string.toUtf8());
    }else{
        qDebug()<<"handle errors here";
        QVariant statusCodev = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug("found error ....code:%d %d",statusCodev.toInt(),(int)reply->error());
        qDebug(qPrintable(reply->errorString()));
    }
    reply->deleteLater();
}

