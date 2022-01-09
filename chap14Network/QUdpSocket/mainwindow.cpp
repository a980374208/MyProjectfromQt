#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pLabSocketState = new QLabel("Socket 状态:");
    m_pLabSocketState->setMinimumWidth(200);
    ui->statusbar->addWidget(m_pLabSocketState);
    m_pUdpSocket = new QUdpSocket(this);
    connect(m_pUdpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(on_SockerStateChange(m_pUdpSocket)));
    connect(m_pUdpSocket,SIGNAL(readyRead()),
            this,SLOT(on_SocketReadrRead()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SockerStateChange(QAbstractSocket::SocketState socketState)
{

    switch(socketState){
    case QAbstractSocket::UnconnectedState:
        m_pLabSocketState->setText("socket状态: UnconnectState");
        break;
    case QAbstractSocket::HostLookupState:
        m_pLabSocketState->setText("socket状态: HostLookupState");
        break;
    case QAbstractSocket::ConnectingState:
        m_pLabSocketState->setText("socket状态: ConnectingState");
        break;
    case QAbstractSocket::ConnectedState:
        m_pLabSocketState->setText("socket状态: ConnectedState");
        break;
    case QAbstractSocket::BoundState:
        m_pLabSocketState->setText("socket状态: BoundState");
        break;
    case QAbstractSocket::ClosingState:
        m_pLabSocketState->setText("socket状态: ClosingState");
        break;
    case QAbstractSocket::ListeningState:
        m_pLabSocketState->setText("socket状态: ListeningState");
        break;
    }
}

void MainWindow::on_SocketReadrRead()
{
    QByteArray datagram;
    datagram.resize(m_pUdpSocket->pendingDatagramSize());
    QHostAddress peerAddr;
    quint16 peerPort;
    m_pUdpSocket->readDatagram(datagram.data(),datagram.size(),&peerAddr,&peerPort);
    QString str = datagram.data();
    QString peer = ("[From "+peerAddr.toString()+":"+
                    QString::number(peerPort)+"]");
    ui->plainTextEdit->appendPlainText(peer+str);
}


void MainWindow::on_actStart_triggered()
{
    quint16 port = ui->spinBindPort->value();
    if(m_pUdpSocket->bind(port)){
        ui->plainTextEdit->appendPlainText("**已绑定成功");
        ui->plainTextEdit->appendPlainText("**端口："
                                           +QString::number(m_pUdpSocket->localPort()));
        ui->actStart->setEnabled(false);
        ui->actStop->setEnabled(true);
    }
}


void MainWindow::on_actStop_triggered()
{
    m_pUdpSocket->abort();
    ui->actStart->setEnabled(true);
    ui->actStop->setEnabled(false);
    ui->plainTextEdit->appendPlainText("**已解除绑定");
}

void MainWindow::on_btnSend_clicked()
{
    QString targetIP = ui->comboTargetIP->currentText();
    QHostAddress targetAddr(targetIP);
    int targetPort = ui->spinTargetPort->value();
    QString msg = ui->editMsg->text();
    QByteArray str = msg.toUtf8();
    m_pUdpSocket->writeDatagram(str,targetAddr,targetPort);
    ui->plainTextEdit->appendPlainText("[out]"+msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();
}


void MainWindow::on_actClear_triggered()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_btnBroadcast_clicked()
{
    int targetPort = ui->spinTargetPort->value();
    QString msg = ui->editMsg->text();
    QByteArray str = msg.toUtf8();
    m_pUdpSocket->writeDatagram(str,QHostAddress::Broadcast,targetPort);
    ui->plainTextEdit->appendPlainText("[out]"+msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

}

