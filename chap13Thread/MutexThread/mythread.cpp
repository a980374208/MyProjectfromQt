#include "mythread.h"
#include <QTime>

void MyThread::run()
{
   m_Stop  = false;
   m_Seq = 0;
   qsrand(QTime::currentTime().second());
   while(!m_Stop){
       if(!m_Paused){
           QMutexLocker locker(&mMutex);
           //mMutex.lock();
           m_Seq++;
           m_DiceValue = 100;
           msleep(10);
//           m_DiceValue =200;
//           msleep(50);
//           m_DiceValue = 300;
//           msleep(50);
           m_DiceValue = qrand();
           msleep(50);
           m_DiceValue = qrand()%6+1;    
           msleep(500);
           //mMutex.unlock();
       }
   }
}

void MyThread::diceBegin()
{
    m_Paused = false;
}

void MyThread::deicePause()
{
    m_Paused = true;
}

void MyThread::stopThread()
{
    m_Stop = true;
}

void MyThread::readValue(int *seq, int *diceValue)
{
    QMutexLocker locker(&mMutex);
//    mMutex.lock();
    *seq = m_Seq;
    *diceValue = m_DiceValue;
//    mMutex.unlock();
}

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}
