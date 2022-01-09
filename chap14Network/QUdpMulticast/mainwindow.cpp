#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        m_pLabSocketState->setText("scoket状态：UnconnectedState");
        break;
    case QAbstractSocket::HostLookupState:
        m_pLabSocketState->setText("scoket状态：HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        m_pLabSocketState->setText("scoket状态：ConnectingState");
        break;

    case QAbstractSocket::ConnectedState:
        m_pLabSocketState->setText("scoket状态：ConnectedState");
        break;

    case QAbstractSocket::BoundState:
        m_pLabSocketState->setText("scoket状态：BoundState");
        break;

    case QAbstractSocket::ClosingState:
        m_pLabSocketState->setText("scoket状态：ClosingState");
        break;

    case QAbstractSocket::ListeningState:
        m_pLabSocketState->setText("scoket状态：ListeningState");
    }
}

void MainWindow::onSocketReadyRead()
{
    while(m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray   datagram;
        datagram.resize(m_pUdpSocket->pendingDatagramSize());
        QHostAddress    peerAddr;
        quint16 peerPort;
        m_pUdpSocket->readDatagram(datagram.data(),datagram.size(),&peerAddr,&peerPort);

//        udpSocket->readDatagram(datagram.data(),datagram.size());
        QString str=datagram.data();

        QString peer="[From "+peerAddr.toString()+":"+QString::number(peerPort)+"] ";

        ui->plainTextEdit->appendPlainText(peer+str);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pLabSocketState=new QLabel("Socket状态：");//
    m_pLabSocketState->setMinimumWidth(200);
    ui->statusbar->addWidget(m_pLabSocketState);


    m_pUdpSocket=new QUdpSocket(this);//用于与连接的客户端通讯的QTcpSocket
//Multicast路由层次，1表示只在同一局域网内
    //组播TTL: 生存时间，每跨1个路由会减1，多播无法跨过大多数路由所以为1
    //默认值是1，表示数据包只能在本地的子网中传送。
    m_pUdpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption,1);


    connect(m_pUdpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    onSocketStateChange(m_pUdpSocket->state());

    connect(m_pUdpSocket,SIGNAL(readyRead()),
            this,SLOT(onSocketReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actStart_triggered()
{
    QString IP = ui->comboIP->currentText();
    m_GroupAddress = QHostAddress(IP);
    int groupPort = ui->spinPort->value();
    if(m_pUdpSocket->bind(QHostAddress::AnyIPv4,groupPort,QUdpSocket::ShareAddress)){
        m_pUdpSocket->joinMulticastGroup(m_GroupAddress);
        ui->plainTextEdit->appendPlainText("**加入组播成功");
        ui->plainTextEdit->appendPlainText("**组播:"+IP);
        ui->plainTextEdit->appendPlainText("端口:"+QString::number(groupPort));
        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);
        ui->comboIP->setEnabled(false);
    }else
        ui->plainTextEdit->appendHtml("**端口绑定失败");


}


void MainWindow::on_actStop_triggered()
{
    m_pUdpSocket->leaveMulticastGroup(m_GroupAddress);
    m_pUdpSocket->abort();
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->comboIP->setEnabled(true);
    ui->plainTextEdit->appendPlainText("**已经解除绑定");
    ui->plainTextEdit->appendPlainText("**已退出组播，解除端口绑定");

}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("239.0.0.0～239.255.255.255为本地管理组播地址范围");
}


void MainWindow::on_btnMulticast_clicked()
{
    quint16     groupPort=ui->spinPort->value();
    QString  msg=ui->editMsg->text();
    QByteArray  datagram=msg.toUtf8();

    m_pUdpSocket->writeDatagram(datagram,m_GroupAddress,groupPort);
    ui->plainTextEdit->appendPlainText("[multicst] "+msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();
}
