#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include <QHostAddress>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_port->setText("8800");
    ui->lineEdit_IP->setText("169.254.139.248");
    m_tcp = new QTcpSocket(this);
    ui->pushButton_setDisConnect->setDisabled(true);
    ui->pushButton_setDisConnect->setDisabled(true);

    m_status = new QLabel;
    QPixmap Connect = QPixmap("://Connect.png");
    QPixmap DisConnect = QPixmap("://DisConnect.png");
    m_status->setPixmap(DisConnect.scaled(20,20));
    ui->statusBar->addWidget(new QLabel("连接状态："));
    ui->statusBar->addWidget(m_status);


    connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
    {
        QByteArray data = m_tcp->readAll();
        ui->textEdit_record->append("客户端say: " + data);
    });

    connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
    {
        m_tcp->close();
        //m_tcp->deleteLater();   // delete m_tcp
        m_status->setPixmap(QPixmap(":/DisConnect.png").scaled(20, 20));
        ui->pushButton_setConnect->setEnabled(true);
        ui->pushButton_setDisConnect->setDisabled(true);
        ui->pushButton_SendMsg->setDisabled(true);
    });
    connect(m_tcp, &QTcpSocket::connected, this, [=](){
        m_status->setPixmap(Connect.scaled(20,20));
        ui->pushButton_setConnect->setEnabled(false);
        ui->pushButton_setDisConnect->setDisabled(false);
        ui->pushButton_SendMsg->setDisabled(false);
    });



}

MainWindow::~MainWindow()
{
    delete ui;
    m_tcp->deleteLater();
}




void MainWindow::on_pushButton_SendMsg_clicked()
{
    QString msg = ui->textEdit_Msg->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->textEdit_record->append("客户端say:"+ msg);
    return ;

}


void MainWindow::on_pushButton_setConnect_clicked()
{
    if(!m_tcp)
        m_tcp = new QTcpSocket(this);
    unsigned short port = ui->lineEdit_port->text().toUShort();
    QString ip = ui->lineEdit_IP->text();
    m_tcp->connectToHost(QHostAddress(ip), port);

}


void MainWindow::on_pushButton_setDisConnect_clicked()
{
   m_tcp->close();

}

