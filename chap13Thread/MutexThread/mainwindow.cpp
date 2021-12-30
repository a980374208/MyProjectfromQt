#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&thread,&MyThread::started,this,&MainWindow::on_threadAStarted);
    connect(&thread,&MyThread::finished,this,&MainWindow::on_threadAFinished);
    connect(&timer,&QTimer::timeout,this,&MainWindow::On_timerOut);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_threadANewValue(int seq, int diceValue)
{
    ui->plainTextEdit->appendPlainText(QString::asprintf(
                                           "第%d次扔筛子，点数为：%d",seq,diceValue));
    QPixmap pic;
    pic.load(QString::asprintf(":/dice/images/d%d.jpg",diceValue));
    ui->LabPic->setPixmap(pic);
}

void MainWindow::on_threadAStarted()
{
    timer.start(100);
    ui->LabA->setText("线程状态：Start");
    ui->btnStartThread->setEnabled(false);
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(true);
    ui->btnStopThread->setEnabled(true);
}

void MainWindow::on_threadAFinished()
{
    timer.stop();
    ui->LabA->setText("线程状态：Finished");
    ui->btnStartThread->setEnabled(true);
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(false);
    ui->btnStopThread->setEnabled(false);
}

void MainWindow::On_timerOut()
{
    int seq,diceValue;
    thread.readValue(&seq,&diceValue);
    static int lastSeq;
    if(seq == 0 || seq == lastSeq) return;
    lastSeq = seq;
    ui->plainTextEdit->appendPlainText(QString::asprintf(
                                           "第%d次扔筛子，点数为：%d",seq,diceValue));
    QPixmap pic;
    pic.load(QString::asprintf(":/dice/images/d%d.jpg",diceValue));
    ui->LabPic->setPixmap(pic);
}


void MainWindow::on_btnStartThread_clicked()
{
    thread.start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(thread.isRunning()){
        thread.stopThread();
        thread.wait();
    }
    event->accept();
}


void MainWindow::on_btnDiceBegin_clicked()
{
    thread.diceBegin();
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(true);
}


void MainWindow::on_btnDiceEnd_clicked()
{
    thread.deicePause();
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);

}


void MainWindow::on_btnStopThread_clicked()
{
    thread.stopThread();

    thread.deicePause();
}

void MainWindow::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

