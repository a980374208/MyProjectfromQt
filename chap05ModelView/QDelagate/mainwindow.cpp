#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

#define FixedColoumnCount 6

void MainWindow::ON_currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);
    if(!current.isValid()) return;
    m_pLabCellPos->setText(QString::asprintf("当前单元格： %d行， %d列",current.row()+1,current.column()+1));
    QStandardItem *item = m_pTheModel->itemFromIndex(current);
    QFont font = item->font();
    ui->actFontBold->setChecked(font.bold());
    m_pLabCellText->setText("单元内容："+item->text());
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pLabCurFiel = new QLabel("当前文件",this);
    m_pLabCellPos = new QLabel("当前单元格",this);
    m_pLabCellText = new QLabel("单元内容",this);
    m_pTheModel = new QStandardItemModel(10,FixedColoumnCount,this);
    m_pTheSelection = new QItemSelectionModel(m_pTheModel);

    ui->tableView->setModel(m_pTheModel);
    ui->tableView->setSelectionModel(m_pTheSelection);
    m_pLabCurFiel->setMinimumWidth(200);
    m_pLabCellPos->setMinimumWidth(150);

    ui->statusbar->addWidget(m_pLabCurFiel);
    ui->statusbar->addWidget(m_pLabCellPos);
    ui->statusbar->addWidget(m_pLabCellText);

    ui->tableView->setItemDelegateForColumn(0,&m_IntSpinDeledate);

    connect(m_pTheSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex))
            ,this,SLOT(ON_currentChanged(QModelIndex,QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniModelFromStringList(QStringList &fileContent)
{

    m_pTheModel->setColumnCount(FixedColoumnCount);
    m_pTheModel->setRowCount(fileContent.count()-1);//fileContent第一行是表头不算-1

    QString header = fileContent.at(0);
    QStringList headerList = header.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    m_pTheModel->setHorizontalHeaderLabels(headerList);
    int j;
    QStandardItem *item;
    for(int i = 1;i<fileContent.count();i++){
        QString lineText = fileContent.at(i);
        QStringList itemList = lineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for(j = 0;j<FixedColoumnCount-1;j++){
            item = new QStandardItem(itemList.at(j));
            m_pTheModel->setItem(i-1,j,item);
        }
        item = new QStandardItem(headerList.at(j));
        item->setCheckable(true);
        if(itemList.at(j) == "1")
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
        m_pTheModel->setItem(i-1,j,item);
    }
}

void MainWindow::SetActAlign(Qt::Alignment actAlign)
{
    if(!m_pTheSelection->hasSelection()) return;
    auto selectionIndexs = m_pTheSelection->selectedIndexes();
    for(int i = 0 ; i< selectionIndexs.count();++i){
        auto index = selectionIndexs.at(i);
        QStandardItem* item = m_pTheModel->itemFromIndex(index);
        item->setTextAlignment(actAlign);
    }

}


void MainWindow::on_actOpen_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString fileNAme = QFileDialog::getOpenFileName(this,"打开一个文件",curPath
                                                    ,"数据文件(*.txt);;所有文件(*.*)");
    if(fileNAme.isEmpty()) return;
    QStringList fileContent;
    QFile file(fileNAme);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        while(!stream.atEnd()){
            QString str = stream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fileContent.append(str);
        }
        file.close();
        m_pLabCurFiel->setText("当前文件："+fileNAme);
        iniModelFromStringList(fileContent);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        ui->actSave->setEnabled(true);
        ui->actAppend->setEnabled(true);
        ui->actDelete->setEnabled(true);
        ui->actInsert->setEnabled(true);
    }
}


void MainWindow::on_actSave_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this,"选择一个文件",curPath,
                                                    "数据文件(*.txt);;所有文件(*.*)");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate/*覆盖*/))
        return;
    QTextStream stream(&file);


    QString str;
    ui->plainTextEdit->clear();
    QStandardItem *item;
    for(int i =0 ;i<m_pTheModel->columnCount();i++){
        item  = m_pTheModel->horizontalHeaderItem(i);
        str = str+item->text()+"\t\t";
    }

    stream<<str<<"\n";
    ui->plainTextEdit->appendPlainText(str);
    int j;
    for(int i = 0; i<m_pTheModel->rowCount();++i){
        str = "";
        for(j = 0;j<m_pTheModel->columnCount()-1;++j){
            item = m_pTheModel->item(i,j);
            str = str+item->text()+"\t\t";
        }
        item = m_pTheModel->item(i,j);
        if(item->checkState() == Qt::Checked)
            str = str + "1";
        else
            str = str + "0";
        stream<<str<<"\n";
        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_actModelData_triggered()
{
    QString str;
    ui->plainTextEdit->clear();
    QStandardItem *item;
    for(int i =0 ;i<m_pTheModel->columnCount();i++){
        item  = m_pTheModel->horizontalHeaderItem(i);
        str = str+item->text()+"\t\t";
    }
    ui->plainTextEdit->appendPlainText(str);
    int j;
    for(int i = 0; i<m_pTheModel->rowCount();++i){
        str = "";
        for(j = 0;j<m_pTheModel->columnCount()-1;++j){
            item = m_pTheModel->item(i,j);
            str = str+item->text()+"\t\t";
        }
        item = m_pTheModel->item(i,j);
        if(item->checkState() == Qt::Checked)
            str = str + "1";
        else
            str = str + "0";
        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem *item ;
    for(int i = 0;i<FixedColoumnCount-1;++i){
        item = new QStandardItem("0");
        itemList<<item;
    }
    QString str = m_pTheModel->headerData(m_pTheModel->columnCount()-1,
                                                                    Qt::Horizontal,Qt::DisplayRole).toString();
    item = new QStandardItem(str);
    item->setCheckState(Qt::Checked);
    itemList<<item;

    m_pTheModel->appendRow(itemList);
    m_pTheSelection->clearSelection();
    QModelIndex index = m_pTheModel->index(m_pTheModel->rowCount()-1,0);
    m_pTheSelection->setCurrentIndex(index,QItemSelectionModel::Select);
}


void MainWindow::on_actInsert_triggered()
{
    QList<QStandardItem*> itemList;
    QStandardItem *item;
    for(int i = 0;i<FixedColoumnCount-1;++i){
        item = new QStandardItem("0");
        itemList<<item;
    }
    QString str = m_pTheModel->headerData(m_pTheModel->columnCount()-1,
                                          Qt::Horizontal,Qt::DisplayRole).toString();
    item = new QStandardItem(str);
    item->setCheckState(Qt::Checked);
    itemList<<item;
    int row = m_pTheSelection->currentIndex().row()+1;
    m_pTheModel->insertRow(row,itemList);
    m_pTheSelection->clearSelection();
    QModelIndex index = m_pTheModel->index(row,m_pTheSelection->currentIndex().column());
    m_pTheSelection->setCurrentIndex(index,QItemSelectionModel::Select);
}


void MainWindow::on_actDelete_triggered()
{
    int curRow = m_pTheSelection->currentIndex().row();
    m_pTheModel->removeRow(curRow);
    QModelIndex index = m_pTheModel->index(curRow,m_pTheSelection->currentIndex().column());
    if(curRow == m_pTheModel->rowCount())
        index = m_pTheModel->index(curRow-1,m_pTheSelection->currentIndex().column());
    m_pTheSelection->setCurrentIndex(index,QItemSelectionModel::Select);
}


void MainWindow::on_actAlignLeft_triggered()
{
    SetActAlign(Qt::AlignLeft);
}


void MainWindow::on_actAlignCenter_triggered()
{
    SetActAlign(Qt::AlignCenter);
}


void MainWindow::on_actAlignRight_triggered()
{
    SetActAlign(Qt::AlignRight);
}


void MainWindow::on_actFontBold_triggered(bool checked)
{
    if(!m_pTheSelection->hasSelection()) return;
    auto selectionIndexs = m_pTheSelection->selectedIndexes();
    for(int i = 0 ; i< selectionIndexs.count();++i){
        auto index = selectionIndexs.at(i);
        QStandardItem* item = m_pTheModel->itemFromIndex(index);
        QFont font = item->font();
        font.setBold(checked);
        item->setFont(font);
    }
}

