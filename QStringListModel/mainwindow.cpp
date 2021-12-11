#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pTheModel = new QStringListModel(this);
    QStringList strList;
    strList<<"item1"<<"item2"<<"item3"<<"item4"<<"item5"<<"item6";
    m_pTheModel->setStringList(strList);
    ui->listView->setModel(m_pTheModel);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <QModelIndex>

void MainWindow::on_btnListAppend_clicked()
{
    m_pTheModel->insertRow(m_pTheModel->rowCount());
    QModelIndex index = m_pTheModel->index(m_pTheModel->rowCount()-1);
    m_pTheModel->setData(index,"additem",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);;
}


void MainWindow::on_btnListInsert_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    m_pTheModel->insertRow(index.row());
    m_pTheModel->setData(index,"new item",Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_btnIniList_clicked()
{
    QStringList strList;
    strList<<"item1"<<"item2"<<"item3"<<"item4"<<"item5"<<"item6";
    m_pTheModel->setStringList(strList);
}


void MainWindow::on_btnListDelete_clicked()
{
    m_pTheModel->removeRow(ui->listView->currentIndex().row());
}


void MainWindow::on_btnListClear_clicked()
{
    m_pTheModel->removeRows(0,m_pTheModel->rowCount());
}


void MainWindow::on_btnTextClear_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_btnTextImport_clicked()
{
    QStringList strList = m_pTheModel->stringList();
    foreach (auto str,strList) {
        ui->plainTextEdit->appendPlainText(str);
    }
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->LabInfo->setText(QString::asprintf("当前项的ModelIndex:%d ",index.row()));
}

