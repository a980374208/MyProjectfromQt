#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pPlayer = new QMediaPlayer;
    m_pPlaylist = new QMediaPlaylist;
    m_pPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    m_pPlayer->setPlaylist(m_pPlaylist);
    //m_pPlayer->setVolume(30);
    ui->sliderVolumn->setValue(30);

    connect(m_pPlayer,&QMediaPlayer::stateChanged,this,&MainWindow::ON_stateChanged);
    connect(m_pPlayer,&QMediaPlayer::positionChanged,this,&MainWindow::ON_posiontionChanged);
    connect(m_pPlayer,&QMediaPlayer::durationChanged,this,&MainWindow::ON_durationChanged);
    connect(m_pPlaylist,&QMediaPlaylist::currentIndexChanged,this,&MainWindow::ON_PLayListIndexChanged);

}



void MainWindow::ON_stateChanged(QMediaPlayer::State state)
{
    ui->btnPlay->setEnabled(!(state == QMediaPlayer::PlayingState));
    ui->btnPause->setEnabled(state == QMediaPlayer::PlayingState);
    ui->btnStop->setEnabled(state == QMediaPlayer::PlayingState);
}

void MainWindow::ON_posiontionChanged(qint64 position)
{
    if(ui->sliderPosition->isSliderDown())
        return;
    ui->sliderPosition->setSliderPosition(position);
    int secs = position/1000;
    int mins = secs/60;
    secs = secs%60;
    m_strPositionTime = QString::asprintf("%d:%d",mins,secs);
    ui->LabRatio->setText(m_strPositionTime+"/"+m_strDurationTime);
}

void MainWindow::ON_durationChanged(qint64 duration)
{
    ui->sliderPosition->setMaximum(duration);
    int secs = duration/1000;
    int mins = secs/60;
    secs = secs%60;
    m_strDurationTime = QString::asprintf("%d:%d",mins,secs);
    ui->LabRatio->setText(m_strPositionTime+"/"+m_strDurationTime);
}

void MainWindow::ON_PLayListIndexChanged(int index)
{
    ui->listWidget->setCurrentRow(index);
    QListWidgetItem *pItem = ui->listWidget->currentItem();
    if(pItem)
        ui->LabCurMedia->setText(pItem->text());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPlay_clicked()
{
    if(ui->listWidget->currentRow() < 0)
        m_pPlaylist->setCurrentIndex(0);
    int pos = ui->listWidget->currentRow();
    m_pPlaylist->setCurrentIndex(pos);
    m_pPlayer->play();
}


void MainWindow::on_btnPause_clicked()
{
    m_pPlayer->pause();
}


void MainWindow::on_btnStop_clicked()
{
    m_pPlayer->stop();
}


void MainWindow::on_btnPrevious_clicked()
{
    m_pPlaylist->previous();

}


void MainWindow::on_btnNext_clicked()
{
    m_pPlaylist->next();

}


void MainWindow::on_btnAdd_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择音频文件";
    QString filter = "音频文件(*.mp3 *.mav *.wma);;mp3文件(*.mps)"
            ";;mav文件(*.mav);;wma文件(*.wma)";
    QStringList fileList = QFileDialog::getOpenFileNames(this,
                                                         dlgTitle,curPath,filter);
    if(fileList.count()<1) return;
    foreach (auto aFile, fileList){
        m_pPlaylist->addMedia(QUrl::fromLocalFile(aFile));
        QFileInfo fileIno(aFile);
        ui->listWidget->addItem(fileIno.fileName());
    }
    if(m_pPlayer->state()!= QMediaPlayer::PlayingState){
        m_pPlaylist->setCurrentIndex(0);
    }
    m_pPlayer->play();
}


void MainWindow::on_btnRemove_clicked()
{
   int pos = ui->listWidget->currentRow();
   QListWidgetItem *pItem = ui->listWidget->takeItem(pos);
   delete pItem;
   m_pPlaylist->removeMedia(pos);
   QString str;
   if(ui->listWidget->currentItem())
       str = ui->listWidget->currentItem()->text();
   ui->LabCurMedia->setText(str);

}


void MainWindow::on_btnClear_clicked()
{
    m_pPlaylist->clear();
    ui->listWidget->clear();
}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int pos = index.row();
    m_pPlaylist->setCurrentIndex(pos);
    m_pPlayer->play();
}


void MainWindow::on_sliderPosition_valueChanged(int value)
{
    m_pPlayer->setPosition(value);
}


void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    m_pPlayer->setVolume(value);
}


void MainWindow::on_btnSound_clicked()
{
    bool isMute = m_pPlayer->isMuted();
    m_pPlayer->setMuted(!isMute);
    isMute = m_pPlayer->isMuted();
    if(isMute)
        ui->btnSound->setIcon(QIcon(":/images/images/mute.bmp"));
    else
        ui->btnSound->setIcon(QIcon(":/images/images/volumn.bmp"));
}

