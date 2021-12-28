#include "mythread.h"
#include <QTime>

void MyThread::run()
{
   m_Stop  = false;
   m_Seq = 0;
   qsrand(QTime::currentTime().second());
   while(!m_Stop){
       if(!m_Paused){
           m_DiceValue = qrand()%6+1;
           m_Seq++;
           emit newValue(m_Seq,m_DiceValue);
           msleep(500);
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

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}
