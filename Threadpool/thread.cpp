#include "thread.h"
#include "ui_thread.h"
#include "mythread.h"
#include <QThreadPool>

Thread::Thread(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Thread)
{
    ui->setupUi(this);
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    connect(this, &Thread::starting, gen , &Generate::recvNum);
    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        emit starting(10000);
        QThreadPool::globalInstance()->start(gen);
    });
    connect(gen, &Generate::sendArray, bubble, &BubbleSort::recvArray);
    connect(gen, &Generate::sendArray, quick, &QuickSort::recvArray);
    connect(gen, &Generate::sendArray, this, [=](QVector<int> list)
    {
        QThreadPool::globalInstance()->start(bubble);
        QThreadPool::globalInstance()->start(quick);
        for(int i=0; i<list.size(); ++i){
            ui->randlist->addItem(QString::number(list.at(i)));
        }
    });

    connect(bubble, &BubbleSort::finish, this, [=](QVector<int> list)
    {
        for(int i=0; i<list.size(); ++i){
            ui->bubblelist->addItem(QString::number(list.at(i)));
        }
    });
    connect(quick, &QuickSort::finish, this, [=](QVector<int> list)
    {
        for(int i=0; i<list.size(); ++i){
            ui->quicklist->addItem(QString::number(list.at(i)));
        }
    });


}

Thread::~Thread()
{
    delete ui;
}

