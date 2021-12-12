#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    m_theModel = new QStandardItemModel;
    m_theSelect = new QItemSelectionModel(m_theModel);
    ui->tableView->setModel(m_theModel);
    QStringList headerList;
    headerList<<"Depth"<<"Measured Depth"<<"Direction"<<"Offset"<<"Quality"<<"Sampled";
    m_theModel->setHorizontalHeaderLabels(headerList);
    ResetTable(5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ResetTable(int rows)
{
    m_theModel->removeRows(0,m_theModel->rowCount());
    m_theModel->setRowCount(rows);
    QString str = m_theModel->headerData(m_theModel->columnCount()-1,Qt::Horizontal,
                           Qt::DisplayRole).toString();
    for(int i= 0; i<rows;i++){  //设置最后一列
        QModelIndex index = m_theModel->index(i,m_theModel->columnCount()-1);
        QStandardItem *item = m_theModel->itemFromIndex(index);
        item->setData(str,Qt::DisplayRole);
        item->setCheckable(true);
        item->setEditable(false);
    }
}


void MainWindow::on_actTabReset_triggered()
{
    ResetTable(10);
}

#include <QFileDialog>

void MainWindow::on_actOpen_triggered()
{
    QString filter = "Qt预定义编码(*.stm)";
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "打开文件";
    QString fileName = QFileDialog::getOpenFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_9);
        qint16 rowCount,colCount;
        stream>>rowCount>>colCount;
        ResetTable(rowCount);
        QString str;
        for(int i=0;i<colCount;++i)
            stream>>str;
        qint16 Depth;
        qreal MeasuredDepth,Direction,Offset;
        QString Quality;
        bool Sampled;
        QModelIndex index;
        QStandardItem *item;
        for(int i = 0;i < rowCount; ++i){
            stream>>Depth;
            index = m_theModel->index(i,0);
            item = m_theModel->itemFromIndex(index);
            item->setData(Depth,Qt::DisplayRole);

            stream>>MeasuredDepth;
            index = m_theModel->index(i,1);
            item = m_theModel->itemFromIndex(index);
            item->setData(MeasuredDepth,Qt::DisplayRole);

            stream>>Direction;
            index = m_theModel->index(i,2);
            item = m_theModel->itemFromIndex(index);
            item->setData(Direction,Qt::DisplayRole);

            stream>>Offset;
            index = m_theModel->index(i,3);
            item = m_theModel->itemFromIndex(index);
            item->setData(Offset,Qt::DisplayRole);

            stream>>Quality;
            index = m_theModel->index(i,4);
            item = m_theModel->itemFromIndex(index);
            item->setData(Quality,Qt::DisplayRole);

            stream>>Sampled;
            index = m_theModel->index(i,5);
            item = m_theModel->itemFromIndex(index);
            if(Sampled)
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
        }

    }
    file.close();
}
void MainWindow::on_actSave_triggered()
{
    QString filter = "Qt预定义编码(*.stm)";
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "保存文件";
    QString fileName = QFileDialog::getSaveFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_9);
        qint16 rowCount,colCount;
        rowCount = m_theModel->rowCount();
        colCount = m_theModel->columnCount();
        stream<<rowCount<<colCount;

        for(int i = 0; i<colCount;++i)
            stream<<m_theModel->horizontalHeaderItem(i)->text();
        qint16 Depth;
        qreal MeasuredDepth,Direction,Offset;
        QString Quality;
        bool Sampled;
        QModelIndex index;
        QStandardItem *item;

        for(int i = 0; i<rowCount; ++i){
            index = m_theModel->index(i,0);
            item = m_theModel->itemFromIndex(index);
            Depth = item->data(Qt::DisplayRole).toInt();
            stream<<Depth;

            index = m_theModel->index(i,1);
            item = m_theModel->itemFromIndex(index);
            MeasuredDepth = item->data(Qt::DisplayRole).toFloat();
            stream<<MeasuredDepth;

            index = m_theModel->index(i,2);
            item = m_theModel->itemFromIndex(index);
            Direction = item->data(Qt::DisplayRole).toFloat();
            stream<<Direction;

            index = m_theModel->index(i,3);
            item = m_theModel->itemFromIndex(index);
            Offset = item->data(Qt::DisplayRole).toFloat();
            stream<<Offset;

            index = m_theModel->index(i,4);
            item = m_theModel->itemFromIndex(index);
            Quality = item->data(Qt::DisplayRole).toString();
            stream<<Quality;

            index = m_theModel->index(i,5);
            item = m_theModel->itemFromIndex(index);
            Sampled = (item->checkState()==Qt::Checked);
            stream<<Sampled;
        }

    }
    file.close();
}


void MainWindow::on_actOpenBin_triggered()
{
    QString filter = "标准编码(*.dat)";
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "打开文件";
    QString fileName = QFileDialog::getOpenFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::LittleEndian);
        //stream.setVersion(QDataStream::Qt_5_9);
        qint16 rowCount,colCount;
        //stream>>rowCount>>colCount;
         stream.readRawData((char*)&rowCount,sizeof(qint16));
         stream.readRawData((char*)&colCount,sizeof(qint16));

        ResetTable(rowCount);
        char* buf;
        uint strlen;
        for(int i=0;i<colCount;++i)
            stream.readBytes(buf,strlen);
       // QString str = QString::fromLocal8Bit(buf,strlen);
        qint16 Depth;
        qreal MeasuredDepth,Direction,Offset;
        QString Quality;
        qint8 Sampled;
        QModelIndex index;
        QStandardItem *item;
        for(int i = 0;i < rowCount; ++i){
            stream.readRawData((char*)&Depth,sizeof(qint16));
            index = m_theModel->index(i,0);
            item = m_theModel->itemFromIndex(index);
            item->setData(Depth,Qt::DisplayRole);

            stream.readRawData((char*)&MeasuredDepth,sizeof(qreal));
            index = m_theModel->index(i,1);
            item = m_theModel->itemFromIndex(index);
            item->setData(MeasuredDepth,Qt::DisplayRole);

            stream.readRawData((char*)&Direction,sizeof(qreal));
            index = m_theModel->index(i,2);
            item = m_theModel->itemFromIndex(index);
            item->setData(Direction,Qt::DisplayRole);

            stream.readRawData((char*)&Offset,sizeof(qreal));
            index = m_theModel->index(i,3);
            item = m_theModel->itemFromIndex(index);
            item->setData(Offset,Qt::DisplayRole);

            stream.readBytes(buf,strlen);
            Quality = QString::fromLocal8Bit(buf,strlen);
            index = m_theModel->index(i,4);
            item = m_theModel->itemFromIndex(index);
            item->setData(Quality,Qt::DisplayRole);

            stream.readRawData((char*)&Sampled,sizeof(qint8));
            index = m_theModel->index(i,5);
            item = m_theModel->itemFromIndex(index);
            if(Sampled)
                item->setCheckState(Qt::Checked);
            else
                item->setCheckState(Qt::Unchecked);
        }

    }
    file.close();
}


void MainWindow::on_actSaveBin_triggered()
{
    QString filter = "Qt预定义编码(*.dat)";
    QString curPath = QCoreApplication::applicationDirPath();
    QString title = "保存文件";
    QString fileName = QFileDialog::getSaveFileName(this,title,curPath,filter);
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::LittleEndian);
        //stream.setVersion(QDataStream::Qt_5_9);

        qint16 rowCount,colCount;
        rowCount = m_theModel->rowCount();
        colCount = m_theModel->columnCount();
        //stream<<rowCount<<colCount;
        stream.writeRawData((char*)&rowCount,sizeof(rowCount));
        stream.writeRawData((char*)&colCount,sizeof(colCount));

        QString str;
        QByteArray array;
        for(int i = 0; i<colCount;++i){
            //stream<<m_theModel->horizontalHeaderItem(i)->text();
            str = m_theModel->horizontalHeaderItem(i)->text();
            array= str.toUtf8();
            stream.writeBytes(array,array.length());
        }

        qint16 Depth;
        qreal MeasuredDepth,Direction,Offset;
        QString Quality;
        qint8 Sampled;
        QModelIndex index;
        QStandardItem *item;

        for(int i = 0; i<rowCount; ++i){
            index = m_theModel->index(i,0);
            item = m_theModel->itemFromIndex(index);
            Depth = item->data(Qt::DisplayRole).toInt();
            stream.writeRawData((char*)&Depth,sizeof(qint16));

            index = m_theModel->index(i,1);
            item = m_theModel->itemFromIndex(index);
            MeasuredDepth = item->data(Qt::DisplayRole).toFloat();
            stream.writeRawData((char*)&MeasuredDepth,sizeof(qreal));

            index = m_theModel->index(i,2);
            item = m_theModel->itemFromIndex(index);
            Direction = item->data(Qt::DisplayRole).toFloat();
            stream.writeRawData((char*)&Direction,sizeof(qreal));

            index = m_theModel->index(i,3);
            item = m_theModel->itemFromIndex(index);
            Offset = item->data(Qt::DisplayRole).toFloat();
            stream.writeRawData((char*)&Offset,sizeof(qreal));

            index = m_theModel->index(i,4);
            item = m_theModel->itemFromIndex(index);
            Quality = item->data(Qt::DisplayRole).toString();
            array= Quality.toUtf8();
            stream.writeBytes(array,array.length());

            index = m_theModel->index(i,5);
            item = m_theModel->itemFromIndex(index);
            Sampled = (item->checkState()==Qt::Checked);
            stream.writeRawData((char*)&Sampled,sizeof(qint8));
        }
    }
    file.close();
}

