#include "mythread.h"
#include "QElapsedTimer"
#include "QDebug"

Generate::Generate(QObject *parent) : QObject(parent)
{

}

//void Generate::recvNum(int num)
//{
//    m_num = num;
//}

void Generate::working(int m)
{
    QElapsedTimer time;

    QVector<int> list;
    time.start();
    for(int i = 0; i<m; ++i){
        list.push_back(rand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug()<<"生成"<<m<<"个随机数总用时"<<milsec<<"毫秒";
    emit sendArray(list);
}




BubbleSort::BubbleSort(QObject *parent):QObject(parent)
{

}

//void BubbleSort::recvArray(QVector<int> list)
//{
//    m_list = list;
//}

void BubbleSort:: working(QVector<int> m_list)
{
    qDebug()<<"冒泡排序的线程地址"<<QThread::currentThread();
    int temp;
    QElapsedTimer time;
    time.start();
    for(int i = 0; i<m_list.size(); ++i){
        for(int j = 0;j<m_list.size()-i-1;++j){
            if(m_list[j]>m_list[j+1]){
                temp = m_list[j];
                m_list[j] = m_list[j+1];
                 m_list[j+1] = temp;
            }
        }
    }
    int milsec = time.elapsed();
    qDebug()<<"冒泡排序用时"<<milsec<<"毫秒";
    emit finish(m_list);
}





QuickSort::QuickSort(QObject *parent):QObject(parent)
{
}

//void QuickSort::recvArray(QVector<int> list)
//{
//    m_list = list;
//}

void QuickSort::qucikSort(QVector<int> &list, int l, int r)
{
    if(l<r){
        int i = l,j = r;
        int x = list[l];
        while(i < j){
            while(i<j && list[j]>=x){
                j--;
            }
            if(i<j){
                list[i++] = list[j];
            }
            while(i<j && list[i]>=x){
                i++;
            }
            if(i<j){
                list[j--] = list[i];
            }
        }
        list[i] = x;
        qucikSort(list, l, i-1);
        qucikSort(list, i+1, r);
    }
}

void QuickSort:: working(QVector<int> m_list)
{
    qDebug()<<"快熟排序的线程地址"<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    qucikSort(m_list,0,m_list.size()-1);
    int milsec = time.elapsed();
    qDebug()<<"快速排序用时"<<milsec<<"毫秒";
    emit finish(m_list);

}
