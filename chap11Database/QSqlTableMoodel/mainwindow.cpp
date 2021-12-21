#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

void MainWindow::ON_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    //ui->actSubmit->setEnabled(m_pSqlTablemodel->isDirty());
    ui->actRevert->setEnabled(m_pSqlTablemodel->isDirty());
}

void MainWindow::ON_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    ui->actRecDelete->setEnabled(current.isValid());
    ui->actRecAppend->setEnabled(current.isValid());
    ui->actRecInsert->setEnabled(current.isValid());
    if(!current.isValid()){
        ui->dbLabPhoto->clear();
        return;
    }
    m_pDataMapper->setCurrentIndex(current.row());
    QSqlRecord curRec = m_pSqlTablemodel->record(current.row());
    if(curRec.isNull("Photo"))
        ui->dbLabPhoto->clear();
    else{
        QByteArray photoArray = curRec.value("Photo").toByteArray();
        QPixmap pix;
        pix.loadFromData(photoArray);
        ui->dbLabPhoto->setPixmap(pix.scaledToWidth(ui->dbLabPhoto->size().width()));
    }


}

void MainWindow::openTable()
{

    m_pSqlTablemodel = new QSqlTableModel(this,db);
    m_pSqlTablemodel->setTable("employee");
    m_pSqlTablemodel->setSort(m_pSqlTablemodel->fieldIndex("EmpNo"),Qt::AscendingOrder);
    if(!m_pSqlTablemodel->select()){//查询数据
        QMessageBox::critical(this,"error","打开数据库表错误"+db.lastError().text());
        return;
    }
    ui->tableView->setModel(m_pSqlTablemodel);
    m_pSelectModel = new QItemSelectionModel(m_pSqlTablemodel);
    ui->tableView->setSelectionModel(m_pSelectModel);
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("empNo"),Qt::Horizontal,"工号");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Name"),Qt::Horizontal,"姓名");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Gender"),Qt::Horizontal,"性别");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Height"),Qt::Horizontal,"身高");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Birthday"),Qt::Horizontal,"出生日期");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Mobile"),Qt::Horizontal,"手机");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Province"),Qt::Horizontal,"省份");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("City"),Qt::Horizontal,"城市");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Department"),Qt::Horizontal,"部门");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Education"),Qt::Horizontal,"学历");
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Salary"),Qt::Horizontal,"工资");

    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Memo"),Qt::Horizontal,"备注"); //这两个字段不再tableView中显示
    m_pSqlTablemodel->setHeaderData(m_pSqlTablemodel->fieldIndex("Photo"),Qt::Horizontal,"照片");

    ui->tableView->setColumnHidden(m_pSqlTablemodel->fieldIndex("Memo"),true);
    ui->tableView->setColumnHidden(m_pSqlTablemodel->fieldIndex("Photo"),true);
    connect(m_pSelectModel,&QItemSelectionModel::currentChanged,this,&MainWindow::ON_currentChanged);
    connect(m_pSelectModel,&QItemSelectionModel::currentRowChanged,this,&MainWindow::ON_currentRowChanged);

    //创建界面组件与数据模型的字段之间的数据映射
    m_pDataMapper = new QDataWidgetMapper;
    m_pDataMapper->setModel(m_pSqlTablemodel);
    m_pDataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    //    dataMapper->setItemDelegate(new QSqlRelationalDelegate(this)); //含有外键的
    //界面组件与tabModel的具体字段之间的联系
    m_pDataMapper->addMapping(ui->dbSpinEmpNo,m_pSqlTablemodel->fieldIndex("empNo"));
    m_pDataMapper->addMapping(ui->dbEditName,m_pSqlTablemodel->fieldIndex("Name"));
    m_pDataMapper->addMapping(ui->dbComboSex,m_pSqlTablemodel->fieldIndex("Gender"));

    m_pDataMapper->addMapping(ui->dbSpinHeight,m_pSqlTablemodel->fieldIndex("Height"));
    m_pDataMapper->addMapping(ui->dbEditBirth,m_pSqlTablemodel->fieldIndex("Birthday"));
    m_pDataMapper->addMapping(ui->dbEditMobile,m_pSqlTablemodel->fieldIndex("Mobile"));

    m_pDataMapper->addMapping(ui->dbComboProvince,m_pSqlTablemodel->fieldIndex("Province"));
    m_pDataMapper->addMapping(ui->dbEditCity,m_pSqlTablemodel->fieldIndex("City"));
    m_pDataMapper->addMapping(ui->dbComboDep,m_pSqlTablemodel->fieldIndex("Department"));

    m_pDataMapper->addMapping(ui->dbComboEdu,m_pSqlTablemodel->fieldIndex("Education"));
    m_pDataMapper->addMapping(ui->dbSpinSalary,m_pSqlTablemodel->fieldIndex("Salary"));

    m_pDataMapper->addMapping(ui->dbEditMemo,m_pSqlTablemodel->fieldIndex("Memo"));

    //    m_pDataMapper->addMapping(ui->dbPhoto,m_pSqlTablemodel->fieldIndex("Photo")); //图片无法直接映射

    m_pDataMapper->toFirst();//移动到首记录

    ui->actOpenDB->setEnabled(false);

    ui->actRecAppend->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actScan->setEnabled(true);

    ui->actPhotoClear->setEnabled(true);
    ui->actPhoto->setEnabled(true);

    ui->groupBoxSort->setEnabled(true);
    ui->groupBoxFilter->setEnabled(true);
    QStringList strList;
    strList<<"男"<<"女";
    bool isEditTable = false;
    m_DelegateSex.setItems(strList,isEditTable);
    ui->tableView->setItemDelegateForColumn(m_pSqlTablemodel->fieldIndex("Gender"),&m_DelegateSex);
    strList.clear();
    strList<<"销售部"<<"技术部"<<"生产部"<<"行政部";
    m_DelegateDepart.setItems(strList,isEditTable);
    ui->tableView->setItemDelegateForColumn(m_pSqlTablemodel->fieldIndex("Department"),&m_DelegateDepart);

}

void MainWindow::GetFiledNames()
{
    QSqlRecord emptyRec = m_pSqlTablemodel->record();
    for(int i = 0 ;i<emptyRec.count();++i){
        ui->comboFields->addItem(emptyRec.fieldName(i));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pSqlTablemodel = nullptr;



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actOpenDB_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(this,"选择数据库文件",QDir::currentPath(),"SQLite数据库(*.db *.db3");
    if(FileName.isEmpty()) return;
//    db = new QSqlDatabase;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(FileName);
    if(!db.open()){
        QMessageBox::warning(this,"打开数据库失败",db.lastError().text());
    }
    openTable();
    GetFiledNames();
}


void MainWindow::on_actRecAppend_triggered()
{
    m_pSqlTablemodel->insertRow(m_pSqlTablemodel->rowCount(),QModelIndex());
    QModelIndex curIndex = m_pSqlTablemodel->index(m_pSqlTablemodel->rowCount()-1,1);
    m_pSelectModel->clearSelection();
    m_pSelectModel->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    m_pSqlTablemodel->setData(m_pSqlTablemodel->index(curIndex.row(),0),2000+m_pSqlTablemodel->rowCount());
    m_pSqlTablemodel->setData(m_pSqlTablemodel->index(curIndex.row(),2),"男");

}


void MainWindow::on_actRecInsert_triggered()
{
    QModelIndex curIndex = m_pSelectModel->currentIndex();
    m_pSqlTablemodel->insertRow(curIndex.row(),QModelIndex());
    m_pSelectModel->clearSelection();
    m_pSelectModel->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    m_pSqlTablemodel->setData(m_pSqlTablemodel->index(curIndex.row()+1,0),2000+m_pSqlTablemodel->rowCount());
    m_pSqlTablemodel->setData(m_pSqlTablemodel->index(curIndex.row()+1,2),"男");
}


void MainWindow::on_actRecDelete_triggered()
{
    QModelIndex curIndex = m_pSelectModel->currentIndex();
    m_pSqlTablemodel->removeRow(curIndex.row(),QModelIndex());

}


void MainWindow::on_actSubmit_triggered()
{
    bool res;
    if(m_pSqlTablemodel == nullptr)
        return;
    if(m_pSqlTablemodel->isDirty()){

        res = m_pSqlTablemodel->submitAll();
    }else {
        QMessageBox::critical(this,"错误","无数据改动");
        return;
    }

    if(!res){
        QMessageBox::information(this,"消息","数据提交错误"+m_pSqlTablemodel->lastError().text());

    }else{
        ui->actRevert->setEnabled(false);
    }
}


void MainWindow::on_actRevert_triggered()
{
    m_pSqlTablemodel->revertAll();
    ui->actRevert->setEnabled(false);
}


void MainWindow::on_actPhotoClear_triggered()
{
    int curRecNo = m_pSelectModel->currentIndex().row();
    QSqlRecord curRec = m_pSqlTablemodel->record(curRecNo);
    curRec.setNull("Photo");
    m_pSqlTablemodel->setRecord(curRecNo,curRec);
    ui->dbLabPhoto->clear();
}


void MainWindow::on_actPhoto_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"照片","","照片(*.jpg)");
    if(fileName.isEmpty()) return;
    QByteArray data;
    QFile *file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    data = file->readAll();
    file->close();
    int curRecNo = m_pSelectModel->currentIndex().row();
    QSqlRecord curRec = m_pSqlTablemodel->record(curRecNo);
    curRec.setValue("Photo",data);
    m_pSqlTablemodel->setRecord(curRecNo,curRec);
    QPixmap pix;
    pix.loadFromData(data);
    ui->dbLabPhoto->setPixmap(pix.scaledToWidth(ui->dbLabPhoto->size().width()));

}


void MainWindow::on_actScan_triggered()
{
    if(m_pSqlTablemodel->rowCount() == 0) return;
    for(int i = 0; i<m_pSqlTablemodel->rowCount();++i){
        QSqlRecord curRec = m_pSqlTablemodel->record(i);
        float salary = curRec.value("Salary").toFloat();
        salary*=1.1;
        curRec.setValue("Salary",salary);
        m_pSqlTablemodel->setRecord(i,curRec);
    }


    if (m_pSqlTablemodel->submitAll())
        QMessageBox::information(this, "消息", "涨工资计算完毕",
                         QMessageBox::Ok,QMessageBox::NoButton);

// 索引方式刷新记录,速度一样
//    float   salary;
//    for (int i=0;i<tabModel->rowCount();i++)
//    {
//        salary=tabModel->data(tabModel->index(i,10)).toFloat();
//        salary=salary*1.1;
//        tabModel->setData(tabModel->index(i,10),salary);
//    }

}


void MainWindow::on_comboFields_currentIndexChanged(int index)
{
    if(ui->radioBtnAscend->isCheckable())
        m_pSqlTablemodel->setSort(index,Qt::AscendingOrder);
    else
        m_pSqlTablemodel->setSort(index,Qt::DescendingOrder);
    m_pSqlTablemodel->select();
}


void MainWindow::on_radioBtnAscend_clicked()
{
    m_pSqlTablemodel->setSort(ui->comboFields->currentIndex(),Qt::AscendingOrder);
    m_pSqlTablemodel->select();

}


void MainWindow::on_radioBtnDescend_clicked()
{
    m_pSqlTablemodel->setSort(ui->comboFields->currentIndex(),Qt::DescendingOrder);
    m_pSqlTablemodel->select();
}


void MainWindow::on_radioBtnMan_clicked()
{
    m_pSqlTablemodel->setFilter("Gender = '男'");
}


void MainWindow::on_radioBtnWoman_clicked()
{
    m_pSqlTablemodel->setFilter("Gender = '女'");
}


void MainWindow::on_radioBtnBoth_clicked()
{
    m_pSqlTablemodel->setFilter("");
}

