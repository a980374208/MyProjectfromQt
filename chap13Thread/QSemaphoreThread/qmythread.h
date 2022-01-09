#ifndef QMYTHREAD_H
#define QMYTHREAD_H

#include <QThread>

class QMyThread : public QThread
{
    Q_OBJECT
public:
    explicit QMyThread();

protected:
    void run()Q_DECL_OVERRIDE;

signals:
private:

    int m_Sec;

};

class QMyThreadShow : public QThread
{
    Q_OBJECT
public:
    explicit QMyThreadShow();

    bool Stop() const;
    void setStop(bool newStop);

protected:
    void run()Q_DECL_OVERRIDE;

signals:
    void newValue(int *data,int count,int seq);




};

#endif // QMYTHREAD_H
