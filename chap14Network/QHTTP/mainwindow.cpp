#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_finished()
{
    QFileInfo fileInfor;
    m_pDownloadFile->close();
    delete m_pDownloadFile;
    m_pDownloadFile = Q_NULLPTR;
    m_pReply->deleteLater();
    m_pReply = Q_NULLPTR;
    if(ui->checkOpen->isChecked()){
        QDesktopServices::openUrl(QUrl::fromLocalFile(
                                      fileInfor.absolutePath()));
        ui->btnDownload->setEnabled(true);
    }

}

void MainWindow::on_readyRead()
{
    m_pDownloadFile->write(m_pReply->readAll());

}

void MainWindow::on_downloadProgress(qint64 bytesRead, qint64 totalBttes)
{
    ui->progressBar->setMaximum(totalBttes);
    ui->progressBar->setValue(bytesRead);

}


void MainWindow::on_btnDefaultPath_clicked()
{
    QString curPath = QDir::currentPath();
    QDir dir(curPath);
    QString sub = "temp";
    dir.mkdir(sub);
    ui->editPath->setText(curPath+"/"+sub+"/");
}


void MainWindow::on_btnDownload_clicked()
{
    QString urlSpec = ui->editURL->text();
    if(urlSpec.isEmpty()){
        QMessageBox::information(this,"error","请输入正确的地址");
        return;
    }
    QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if(!newUrl.isValid()){
        QMessageBox::information(this,"error",
                                 QString("无效的URL:%1 \n 错误信息： %2")
                                 .arg(urlSpec,newUrl.errorString()));
        return;
    }
    QString tempDir = ui->editPath->text().trimmed();
    if(tempDir.isEmpty()){
        QMessageBox::information(this,"error","目录无效");
        return;
    }
    QString fullFileName = tempDir+newUrl.fileName();
    if(QFile::exists(fullFileName)){
        QFile::remove(fullFileName);
    }
    m_pDownloadFile = new QFile(fullFileName);
    if(!m_pDownloadFile->open(QIODevice::WriteOnly)){
        QMessageBox::information(this,"error","文件打开失败");
        return;
    }
    ui->btnDownload->setEnabled(false);
    m_pReply = m_NetworkManger.get(QNetworkRequest(newUrl));
    connect(m_pReply,SIGNAL(finished()),this,SLOT(on_finished()));
    connect(m_pReply,SIGNAL(readyRead()),this,SLOT(on_readyRead()));
    connect(m_pReply,SIGNAL(downloadProgress(qint64,qint64)),
            this,SLOT(on_downloadProgress(qint64,qint64)));
}

