#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QMutex>

class MyThread : public QThread
{
    Q_OBJECT

private:
    QMutex mMutex;
    int m_Seq = 0;
    int m_DiceValue;
    int m_Paused = true;
    int m_Stop = false;

protected:

    void run()Q_DECL_OVERRIDE;

public:
    void diceBegin();
    void deicePause();
    void stopThread();

    void readValue(int *seq,int *diceValue);

public:
    explicit MyThread(QObject *parent = nullptr);


};

#endif // MYTHREAD_H
