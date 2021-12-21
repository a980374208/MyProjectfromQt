#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pFileModel = new QFileSystemModel(this);
    m_pFileModel->setRootPath(QDir::currentPath());
    ui->treeView->setModel(m_pFileModel);
    ui->tableView->setModel(m_pFileModel);
    ui->listView->setModel(m_pFileModel);
    ui->tableView->verticalHeader()->setVisible(false);
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->listView,SLOT(setRootIndex(QModelIndex)));
    connect(ui->treeView,SIGNAL(clicked(QModelIndex)),ui->tableView,SLOT(setRootIndex(QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->lab_Name->setText(m_pFileModel->fileName(index));
    ui->lab_Type->setText(m_pFileModel->type(index));
    ui->label_2->setText(m_pFileModel->filePath(index));
    unsigned sz = m_pFileModel->size(index)/1024;
    if(sz<1024)
        ui->lab_Size->setText(QString::asprintf("%d KB",sz));
    else
        ui->lab_Size->setText(QString::asprintf("%.2f MB",(float)sz/1024));
    ui->checkBox->setChecked(m_pFileModel->isDir(index));
}

