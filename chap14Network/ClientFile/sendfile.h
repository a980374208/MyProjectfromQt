#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include "QTcpSocket"

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QObject *parent = nullptr);

    void ConnectServer(unsigned short port,QString ip);
    void StartSendFile(QString path);

signals:
    void ConnectOk();
    void ConnectOver();
    void CurPercent(int percent);
private:
    QTcpSocket* m_tcp;

};

#endif // SENDFILE_H
