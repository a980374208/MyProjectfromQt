#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sendfile.h"
#include "QThread"
#include "QMessageBox"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Port->setText("8800");
    ui->lineEdit_IP->setText("127.0.0.1");
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    m_t = new QThread;
    SendFile* sendfile = new SendFile();
    sendfile->moveToThread(m_t);
    m_t->start();
    connect(this,&MainWindow::StartConnect, sendfile, &SendFile::ConnectServer);
    connect(sendfile,&SendFile::ConnectOk, this, [=](){
        QMessageBox::information(this,"连接成功","连接服务器成功");
        ui->pushButton_SendFile->setEnabled(true);
        ui->pushButton_SetConnect->setDisabled(true);
    });
    connect(sendfile,&SendFile::ConnectOver, this, [=](){
        QMessageBox::information(this,"连接断开","已与服务器断开连接");
        ui->pushButton_SendFile->setEnabled(false);
        ui->pushButton_SetConnect->setDisabled(false);
    });
    connect(this, &MainWindow::StartSend,sendfile,&SendFile::StartSendFile);
    connect(sendfile,&SendFile::CurPercent, ui->progressBar, &QProgressBar::setValue);
    ui->pushButton_SendFile->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_SelectFile_clicked()
{
    QString Path = QFileDialog::getOpenFileName();
    if(Path.isEmpty()){
        QMessageBox::warning(this,"错误", "路径不能为空");
        return;
    }
    ui->lineEdit_Path->setText(Path);
    ui->progressBar->setValue(0);
}


void MainWindow::on_pushButton_SetConnect_clicked()
{
    unsigned short port = ui->lineEdit_Port->text().toUShort();
    QString ip = ui->lineEdit_IP->text();

    emit StartConnect(port, ip);
}


void MainWindow::on_pushButton_SendFile_clicked()
{
    QString Path = ui->lineEdit_Path->text();
    emit StartSend(Path);
}

