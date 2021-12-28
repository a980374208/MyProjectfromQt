#include "dialog.h"
#include "ui_dialog.h"

void Dialog::on_threadANewValue(int seq, int diceValue)
{
    ui->plainTextEdit->appendPlainText(QString::asprintf(
                                           "第%d次扔筛子，点数为：%d",seq,diceValue));
    QPixmap pic;
    pic.load(QString::asprintf(":/dice/images/d%d.jpg",diceValue));
    ui->LabPic->setPixmap(pic);
}

void Dialog::on_threadAStarted()
{
    ui->LabA->setText("线程状态：Start");
    ui->btnStartThread->setEnabled(false);
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(true);
    ui->btnStopThread->setEnabled(true);
}

void Dialog::on_threadAFinished()
{
    ui->LabA->setText("线程状态：Finished");
    ui->btnStartThread->setEnabled(true);
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(false);
    ui->btnStopThread->setEnabled(false);
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&thread,&MyThread::started,this,&Dialog::on_threadAStarted);
    connect(&thread,&MyThread::finished,this,&Dialog::on_threadAFinished);
    connect(&thread,&MyThread::newValue,this,&Dialog::on_threadANewValue);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnStartThread_clicked()
{
    thread.start();
}

void Dialog::closeEvent(QCloseEvent *event)
{
    if(thread.isRunning()){
        thread.stopThread();
        thread.wait();
    }
    event->accept();
}


void Dialog::on_btnDiceBegin_clicked()
{
    thread.diceBegin();
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(true);
}


void Dialog::on_btnDiceEnd_clicked()
{
    thread.deicePause();
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);

}


void Dialog::on_btnStopThread_clicked()
{
    thread.stopThread();
}


void Dialog::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

