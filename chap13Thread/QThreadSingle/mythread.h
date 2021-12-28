#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT

private:
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

public:
    explicit MyThread(QObject *parent = nullptr);

signals:
    void newValue(int seq,int diceValue);

};

#endif // MYTHREAD_H
