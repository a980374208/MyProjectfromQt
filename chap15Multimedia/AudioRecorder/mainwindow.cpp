#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pProbe = new QAudioProbe(this);
    m_pRecorder = new QAudioRecorder(this);
    connect(m_pRecorder,&QAudioRecorder::stateChanged,this,&MainWindow::ON_stateChange);
    connect(m_pRecorder,&QAudioRecorder::durationChanged,this,&MainWindow::ON_durationChanged);
    connect(m_pProbe,&QAudioProbe::audioBufferProbed,this,&MainWindow::ON_audioBufferProbed);
    m_pProbe->setSource(m_pRecorder);
    if(m_pRecorder->defaultAudioInput().isEmpty()) return;
    foreach(auto device,m_pRecorder->audioInputs()){
        ui->comboDevices->addItem(device);
    }
    foreach(auto codec,m_pRecorder->supportedAudioCodecs()){
        ui->comboCodec->addItem(codec);
    }
    foreach(auto sampRate,m_pRecorder->supportedAudioSampleRates()){
        ui->comboSampleRate->addItem(QString::number(sampRate));
    }
    ui->comboChannels->addItem("1");
    ui->comboChannels->addItem("2");
    ui->comboChannels->addItem("3");

    ui->sliderQuality->setRange(0,int(QMultimedia::VeryHighQuality));
    ui->sliderQuality->setValue(int(QMultimedia::NormalQuality));

    ui->comboBitrate->addItem("32000");
    ui->comboBitrate->addItem("640000");
    ui->comboBitrate->addItem("96000");
    ui->comboBitrate->addItem("128000");
    ui->editOutputFile->setEnabled(false);

}
void MainWindow::ON_stateChange(QMediaRecorder::State state)
{
    ui->actRecord->setEnabled(state != QMediaRecorder::RecordingState);
    ui->actPause->setEnabled(state == QMediaRecorder::RecordingState);
    ui->actStop->setEnabled(state != QMediaRecorder::StoppedState);
    if(state == QMediaRecorder::RecordingState||state == QMediaRecorder::RecordingState){
        ui->btnGetFile->setEnabled(0);
    }else{
        ui->btnGetFile->setEnabled(1);
    }


}

void MainWindow::ON_durationChanged(qint64 duration)
{
    ui->LabPassTime->setText(QString("录制了%1秒").arg(duration/1000));
}

void MainWindow::ON_audioBufferProbed(QAudioBuffer buffer)
{
    ui->spin_byteCount->setValue(buffer.byteCount());//缓冲区字节数
    ui->spin_duration->setValue(buffer.duration()/1000);//缓冲区时长
    ui->spin_frameCount->setValue(buffer.frameCount());//缓冲区帧数
    ui->spin_sampleCount->setValue(buffer.sampleCount());//缓冲区采样数

    QAudioFormat audioFormat=buffer.format();//缓冲区格式
    ui->spin_channelCount->setValue(audioFormat.channelCount()); //通道数
    ui->spin_sampleSize->setValue(audioFormat.sampleSize());//采样大小
    ui->spin_sampleRate->setValue(audioFormat.sampleRate());//采样率
    ui->spin_bytesPerFrame->setValue(audioFormat.bytesPerFrame());//每帧字节数

    if (audioFormat.byteOrder()==QAudioFormat::LittleEndian)
        ui->edit_byteOrder->setText("LittleEndian");//字节序
    else
        ui->edit_byteOrder->setText("BigEndian");

    ui->edit_codec->setText(audioFormat.codec());//编码格式

    if (audioFormat.sampleType()==QAudioFormat::SignedInt)//采样点类型
        ui->edit_sampleType->setText("SignedInt");
    else if(audioFormat.sampleType()==QAudioFormat::UnSignedInt)
        ui->edit_sampleType->setText("UnSignedInt");
    else if(audioFormat.sampleType()==QAudioFormat::Float)
        ui->edit_sampleType->setText("Float");
    else
        ui->edit_sampleType->setText("Unknown");


}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <QFileDialog>

void MainWindow::on_btnGetFile_clicked()
{
    QString strFilename = QFileDialog::getSaveFileName(this,"选择存放的文件路径及确定文件名","","wav文件(.wav)");
    if(strFilename.isEmpty()) return;
    ui->editOutputFile->setText(strFilename);

}
#include <QMessageBox>

void MainWindow::on_actRecord_triggered()
{
    if(m_pRecorder->state() == QMediaRecorder::StoppedState){
        QString strSelectedFile = ui->editOutputFile->text().trimmed();
        if(strSelectedFile.isEmpty()){
            QMessageBox::critical(this,"error","请设置正确的输出文件");
            return;
        }

        if(QFile::exists(strSelectedFile))
            if(!QFile::remove(strSelectedFile)){
                QMessageBox::critical(this,"error","文件正在被占用");
                return;
            }

    m_pRecorder->setOutputLocation(QUrl::fromLocalFile(strSelectedFile));
    m_pRecorder->setAudioInput(ui->comboDevices->currentText());
    }
    QAudioEncoderSettings settings; //音频编码设置
    settings.setCodec(ui->comboCodec->currentText());//编码
    settings.setSampleRate(ui->comboSampleRate->currentText().toInt());//采样率
    settings.setBitRate(ui->comboBitrate->currentText().toInt());//比特率
    settings.setChannelCount(ui->comboChannels->currentText().toInt()); //通道数
    settings.setQuality(QMultimedia::EncodingQuality(ui->sliderQuality->value())); //品质
    if (ui->radioQuality->isChecked())//编码模式为固定品质,自动决定采样率，采样点大小
        settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
    else
        settings.setEncodingMode(QMultimedia::ConstantBitRateEncoding);//固定比特率

    m_pRecorder->setAudioSettings(settings); //音频设置

    m_pRecorder->record();
}


void MainWindow::on_actPause_triggered()
{
    m_pRecorder->pause();
}


void MainWindow::on_actStop_triggered()
{
    m_pRecorder->stop();
}


void MainWindow::on_actQuit_triggered()
{

    delete this;
}

