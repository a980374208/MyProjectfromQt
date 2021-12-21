#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QToolBar * toolbar = new QToolBar;
    toolbar->addAction(ui->actOpenDB);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(toolbar);
    layout->addWidget(ui->tableView);
    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_actOpenDB_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"选择数据库","","SQLite数据库(*.db *.db3)");
    if(fileName.isEmpty())
            return;
    m_Db = QSqlDatabase::addDatabase("QSQLITE");
    m_Db.setDatabaseName(fileName);
    if(!m_Db.open()){
        QMessageBox::warning(this,"数据库打开错误",m_Db.lastError().text());
        return;
    }
    m_pTableModel = new QSqlRelationalTableModel(this,m_Db);
    m_pTableModel->setTable("studInfo");
    m_pTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_pSelectionModel = new QItemSelectionModel(m_pTableModel);
    m_pTableModel->setSort(0,Qt::AscendingOrder);
    m_pTableModel->setHeaderData(0,Qt::Horizontal,"学号");
    m_pTableModel->setHeaderData(1,Qt::Horizontal,"姓名");
    m_pTableModel->setHeaderData(2,Qt::Horizontal,"性别");
    m_pTableModel->setHeaderData(3,Qt::Horizontal,"学院");
    m_pTableModel->setHeaderData(4,Qt::Horizontal,"专业");

    m_pTableModel->setRelation(3,QSqlRelation(
                                   "departments","departID","department"));  //1：需要连接的表明2：关联字段3：显示字段
    m_pTableModel->setRelation(4,QSqlRelation("majors","majorID","major"));

    ui->tableView->setItemDelegate(
                new QSqlRelationalDelegate(/*ui->tableView*/));



    ui->tableView->setModel(m_pTableModel);
    ui->tableView->setSelectionModel(m_pSelectionModel);

    m_pTableModel->select();

    ui->actOpenDB->setEnabled(false);

}

