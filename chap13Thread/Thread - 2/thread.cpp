#include "thread.h"
#include "ui_thread.h"
#include "mythread.h"

Thread::Thread(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Thread)
{
    ui->setupUi(this);
    QThread* t1 = new QThread;
    QThread* t2 = new QThread;
    QThread* t3 = new QThread;

    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);



    connect(this, &Thread::starting, gen , &Generate::working);
    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        emit starting(10000);
        t1->start();
    });
    connect(gen, &Generate::sendArray, bubble, &BubbleSort::working);
    connect(gen, &Generate::sendArray, quick, &QuickSort::working);
    connect(gen, &Generate::sendArray, this, [=](QVector<int> list)
    {
        t2->start();
        t3->start();
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

