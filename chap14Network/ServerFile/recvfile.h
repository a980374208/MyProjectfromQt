#ifndef RECVFILE_H
#define RECVFILE_H

#include <QThread>
#include <QTcpSocket>

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QTcpSocket* soc,QObject *parent = nullptr);

signals:
    void over();
protected:
    void run() override;

private:
    QTcpSocket* m_soc;
};

#endif // RECVFILE_H
