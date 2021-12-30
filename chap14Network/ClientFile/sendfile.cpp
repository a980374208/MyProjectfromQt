#include "sendfile.h"

#include <QFile>
#include <QFileInfo>
#include <QHostAddress>


SendFile::SendFile(QObject *parent) : QObject(parent)
{

}

void SendFile::ConnectServer(unsigned short port, QString ip)
{
     m_tcp = new QTcpSocket(this);
     m_tcp->connectToHost(QHostAddress(ip), port);
     connect(m_tcp, &QTcpSocket::connected,this,[=](){
         emit ConnectOk();
     });
     connect(m_tcp, &QTcpSocket::disconnected,this ,[=](){
         emit ConnectOver();
         m_tcp->close();
     });
}

void SendFile::StartSendFile(QString path)
{
    QFileInfo info(path);
    QFile file(path);
    int fileSize = info.size();
    file.open(QFile::ReadOnly);
    int num = 0;
    while(!file.atEnd()){
        if(num == 0)
            m_tcp->write((char*)&fileSize,4);
        QByteArray line = file.readLine();
        num += line.size();
        int percent = (num * 100/ fileSize);
        m_tcp->write(line);
        emit CurPercent(percent);
    }


}
