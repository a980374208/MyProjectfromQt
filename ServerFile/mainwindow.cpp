#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recvfile.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_TSr = new QTcpServer(this);
    ui->lineEdit_Port->setText("8800");
    connect(m_TSr,&QTcpServer::newConnection,this,[=](){
        //qDebug()<<"starttttttttttttttt";
        m_TSc = m_TSr->nextPendingConnection();
        RecvFile* recvfile = new RecvFile(m_TSc,this);
        recvfile->start();
        connect(recvfile, &RecvFile::over, this,[=](){
            recvfile->exit();
            recvfile->wait();
            //recvfile->deleteLater();
            QMessageBox::information(this,"成功","文件接收完毕");
        });
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_SetListean_clicked()
{
    unsigned short Port = ui->lineEdit_Port->text().toUShort();
    if(!m_TSr->isListening()){
        m_TSr->listen(QHostAddress::Any, Port);
        QMessageBox::information(this,"成功","服务器开启监听成功");
    }else{
        QMessageBox::warning(this,"警告","请勿重复开启监听");
    }

}
