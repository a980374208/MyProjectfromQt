#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_port->setText("8800");
    m_s = new QTcpServer(this);
    connect(m_s, &QTcpServer::newConnection, this, [=](){
        m_tcp = m_s->nextPendingConnection();

        m_status->setPixmap(QPixmap(":/Connect.png").scaled(20, 20));
        // 检测是否可以接收数据
        connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
        {
             QByteArray data = m_tcp->readAll();
             ui->textEdit_record->append("客户端say: " + data);
        });

        connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
        {
            m_tcp->close();
            m_tcp->deleteLater();   // delete m_tcp
            m_status->setPixmap(QPixmap(":/DisConnect.png").scaled(20, 20));
        });
    });
    m_status = new QLabel;
    QPixmap Connect = QPixmap("://Connect.png");
    QPixmap DisConnect = QPixmap("://DisConnect.png");
    m_status->setPixmap(DisConnect.scaled(20,20));
    ui->statusBar->addWidget(new QLabel("连接状态："));
    ui->statusBar->addWidget(m_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_setListen_clicked()
{

    unsigned short port = ui->lineEdit_port->text().toUShort();
    if(!m_s)
        m_s = new QTcpServer(this);
    m_s->listen(QHostAddress::Any,port);
    return;

}


void MainWindow::on_pushButton_SendMsg_clicked()
{
    QString msg = ui->textEdit_Msg->toPlainText();
    m_tcp->write(msg.toUtf8());
    ui->textEdit_record->append("服务器say:"+ msg);
    return ;

}

