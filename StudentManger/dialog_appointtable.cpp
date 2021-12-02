#include "dialog_appointtable.h"
#include "ui_dialog_appointtable.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

CDialog_AppointTable::CDialog_AppointTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialog_AppointTable)
{
    ui->setupUi(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_CurrentSelectedRow = -1;
    //QTimer::singleShot(0,this,&CDialog_AppointTable::ON_ShowTable);
}

CDialog_AppointTable::~CDialog_AppointTable()
{
    delete ui;
}

void CDialog_AppointTable::ON_SLOT_ReciveNoCounClass(QString &a)
{
    m_strSqlNoCounselorClass = a;
    role = 1;
    ON_ShowTable();
    if(m_listNoCounselorClass.isEmpty()){
        QMessageBox::information(this,tr("infor"),tr("当前没有班级没有导员。"));
    }
}

void CDialog_AppointTable::ON_SLOT_ReciveNoTeaCourse(QString &a)
{
    m_strSqlNoTeacherCourse = a;
    role = 2;
    ON_ShowTable();
    if(m_listNoTeacherClass.isEmpty()){
        QMessageBox::information(this,tr("infor"),tr("当前没有课程没有教师。"));
    }
}

void CDialog_AppointTable::ON_ShowTable()
{
    if(role == 1){
        m_listNoCounselorClass.clear();
        QMap<int,QString>                 tempmap;

        query.exec(m_strSqlNoCounselorClass);
        while(query.next()){
            tempmap[0] = query.value(0).toString();
            qDebug()<<"query ="<<query.value(0).toString();
            tempmap[1] = query.value(1).toString();
            tempmap[2] = query.value(2).toString();
            tempmap[3] = query.value(3).toString();
            m_listNoCounselorClass.push_back(tempmap);
        }
        QMap<int,QString>                 tempmap1;
        int size = m_listNoCounselorClass.size();
        ui->tableWidget->setRowCount(size);
        ui->tableWidget->setColumnCount(4);
        QStringList header;
        header<<tr("ClassID")<<tr("ClassNametr")<<tr("Belong")<<tr("TeacherID");
        ui->tableWidget->setHorizontalHeaderLabels(header);
        for(int index = 0;index<size;++index){
            tempmap1 = m_listNoCounselorClass.at(index);
            ui->tableWidget->setItem(index,0,new QTableWidgetItem(tempmap1[0]));
            ui->tableWidget->setItem(index,1,new QTableWidgetItem(tempmap1[1]));
            ui->tableWidget->setItem(index,2,new QTableWidgetItem(tempmap1[2]));
            ui->tableWidget->setItem(index,3,new QTableWidgetItem(tempmap1[3]));
        }
    }else if(role == 2){
        m_listNoTeacherClass.clear();
        QMap<int,QString>                 tempmap;

        query.exec(m_strSqlNoTeacherCourse);
        while(query.next()){
            tempmap[0] = query.value(0).toString();
            tempmap[1] = query.value(1).toString();
            tempmap[2] = query.value(2).toString();
            tempmap[3] = query.value(3).toString();
            tempmap[4] = query.value(4).toString();
            m_listNoTeacherClass.push_back(tempmap);
        }
        QMap<int,QString>                 tempmap1;
        int size = m_listNoTeacherClass.size();
        ui->tableWidget->setRowCount(size);
        ui->tableWidget->setColumnCount(5);
        QStringList header;
        header<<tr("CourseID")<<tr("CourseName")<<tr("Scheduling")<<tr("CourseCredit")<<tr("CourseType");
        ui->tableWidget->setHorizontalHeaderLabels(header);
        for(int index = 0;index<size;++index){
            tempmap1 = m_listNoTeacherClass.at(index);
            ui->tableWidget->setItem(index,0,new QTableWidgetItem(tempmap1[0]));
            ui->tableWidget->setItem(index,1,new QTableWidgetItem(tempmap1[1]));
            ui->tableWidget->setItem(index,2,new QTableWidgetItem(tempmap1[2]));
            ui->tableWidget->setItem(index,3,new QTableWidgetItem(tempmap1[3]));
            ui->tableWidget->setItem(index,3,new QTableWidgetItem(tempmap1[4]));
        }
    }
}

void CDialog_AppointTable::ON_SLOT_ReciverID(QString a)
{
    m_strTeacherID = a;
}



void CDialog_AppointTable::on_pushButton_OK_clicked()
{
    if(m_CurrentSelectedRow == -1){
        QMessageBox::warning(this,tr("error"),tr("请先选择一行数据"));
        return;
    }
    if(role == 1){
        QString CourseID = ui->tableWidget->item(m_CurrentSelectedRow,0)->text();
        QString strSql = QString("update ClassInfor"
                                 " set TeacherID = '%1'"
                                 " where ClassID = '%2'").arg(m_strTeacherID,CourseID);
        QString strSql2 = QString("select TeacherID,TeacherName,Belong from TeacherInfor where TeacherID = '%1'").arg(m_strTeacherID);
        query.exec(strSql2);
        query.next();
        QString TeacherID = query.value(0).toString();
        QString TeacherName = query.value(1).toString().simplified();
        QString Belong = query.value(2).toString();
        QString Permissions = QString(tr("辅导员"));
        QString strSql3 = QString("insert into TeacherInfor(TeacherID,TeacherName,Belong,Permissions) values('%1','%2','%3','%4');"
                                  ).arg(TeacherID,TeacherName,Belong,Permissions);
        if(query.exec(strSql)){
            if(query.exec(strSql3)){
                ON_ShowTable();
                QMessageBox::information(this,tr("success"),tr("set the coun successed."));
                return;
            }
        }
    }else if(role == 2){


        QString CourseID = ui->tableWidget->item(m_CurrentSelectedRow,0)->text();
        QString strSql = QString("update Teacher_Course "
                                 " set TeacherID = '%1'"
                                 " where CourseId = '%2';").arg(m_strTeacherID,CourseID);
        if(query.exec(strSql)){
            ON_ShowTable();
            emit UpdateView();
            QMessageBox::information(this,tr("success"),tr("set the Teacher successed."));
            return;
        }
    }
}


void CDialog_AppointTable::on_tableWidget_cellClicked(int row, int column)
{
    m_CurrentSelectedRow = row;
}


void CDialog_AppointTable::on_pushButton_Cancel_clicked()
{
    close();
}

