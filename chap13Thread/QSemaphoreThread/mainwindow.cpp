#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&m_ThreadProducer,SIGNAL(started()),
            this,SLOT(ON_ProducerStarted()));
    connect(&m_ThreadProducer,SIGNAL(finished()),
            this,SLOT(ON_ProducerFinished()));
    connect(&m_ThreadConsumer,SIGNAL(started()),
            this,SLOT(ON_ConsumerStarted()));
    connect(&m_ThreadProducer,SIGNAL(finished()),
            this,SLOT(ON_ConsumerFinished()));
    connect(&m_ThreadConsumer,SIGNAL(newValue(int*,int,int)),
            this,SLOT(ON_ConsumerValueChanged(int*,int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_ThreadConsumer.isRunning()){
        m_ThreadConsumer.terminate();
        m_ThreadConsumer.wait();
    }
    if(m_ThreadProducer.isRunning()){
        m_ThreadProducer.terminate();
        m_ThreadConsumer.wait();
    }
    event->accept();
}


void MainWindow::on_btnStartThread_clicked()
{
    m_ThreadConsumer.start();
    m_ThreadProducer.start();

    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);
}

void MainWindow::ON_ProducerStarted()
{
   ui->LabProducter->setText(QString::asprintf("生产者状态:started"));
}

void MainWindow::ON_ProducerFinished()
{
   ui->LabProducter->setText("生产者状态:finished");
}

void MainWindow::ON_ConsumerStarted()
{
    ui->LabConsumer->setText(QString::asprintf("消费者状态:started"));
}

void MainWindow::ON_ConsumerFinished()
{

    ui->LabConsumer->setText("消费者状态:finished");
}

void MainWindow::ON_ConsumerValueChanged(int *data, int conunter, int seq)
{
    QString str = QString::asprintf("第%d组数据：",seq);
    for(int i = 0;i<conunter;i++){
        str = str+QString::asprintf(" %d",*data);
        data++;
    }
    ui->plainTextEdit->appendPlainText(str);
}


void MainWindow::on_btnStopThread_clicked()
{
    m_ThreadConsumer.terminate();
    m_ThreadProducer.terminate();
    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);
}


void MainWindow::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

