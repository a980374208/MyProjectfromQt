#include "recvfile.h"
#include <QFile>
#include <QtDebug>

RecvFile::RecvFile(QTcpSocket* soc,QObject *parent) : QThread(parent)
{
    m_soc = soc;
}

void RecvFile::run()
{
    QFile* file = new QFile("recv.txt");
    file->open(QFile::WriteOnly);
    qDebug()<<"11111111111";
    int count = 0;
    int total = 0;
    connect(m_soc,&QTcpSocket::readyRead, this, [=]()mutable{
         qDebug()<<"22222222222222";
//        static int count = 0;
//        static int total = 0;
        if(count == 0){
            m_soc->read((char*)&total,4);
        }
        QByteArray all = m_soc->readAll();
        count += all.size();
        file->write(all);
        if(count == total){
            m_soc->close();
            m_soc->deleteLater();
            file->close();
            //file->deleteLater();
            emit over();
        }  
    });
    exec();
}
