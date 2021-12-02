#include "dialog_addcourse.h"
#include "ui_dialog_addcourse.h"
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

CDialog_AddCourse::CDialog_AddCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialog_AddCourse)
{
    ui->setupUi(this);
    QRegExp rx("[0-9]{5}");
    ui->lineEdit_ID->setValidator(new QRegExpValidator(rx, this));
    QRegExp rx1("^[\\一-\\龥]{0,}$");
     QRegExp rx2("^150$|^(\\d|[1-9]\\d)(\\.\\d+)*$");
    ui->lineEdit_Name->setValidator(new QRegExpValidator(rx1, this));
    ui->lineEdit_Name->setMaxLength(10);
    ui->lineEdit_Achi->setValidator(new QRegExpValidator(rx2, this));
    ui->lineEdit_Credit->setValidator(new QRegExpValidator(rx2, this));
    //ui->lineEdit_ClassID->setValidator(new QRegExpValidator(rx2, this));
}

CDialog_AddCourse::~CDialog_AddCourse()
{
    delete ui;
}

void CDialog_AddCourse::on_pushButton_OK_clicked()
{
    QString ID = ui->lineEdit_ID->text();
    QString Name = ui->lineEdit_Name->text();
    QString Achi = ui->lineEdit_Achi->text();
    QString Credit = ui->lineEdit_Credit->text();
    QString Type = ui->comboBox_Type->currentText();
    //QString ClassID = ui->lineEdit_ClassID->text();
    if(ID.isEmpty()||Name.isEmpty()||Achi.isEmpty()||Credit.isEmpty()){
        QMessageBox::warning(this,tr("error"),tr("请把内容填写完整。"));
        return;
    }
    QString strSql = QString ("select CourseID from CourseInfor where CourseID = '%1'").arg(ID);
    QSqlQuery query;
    query.exec(strSql);
    if(query.next()){
        QMessageBox::warning(this,tr("error"),tr("已存在该课程ID请更换课程ID"));
        return;
    }
    qDebug()<<ID<<Name<<Achi<<Credit<<Type;
    QString strSql1 = QString("insert into CourseInfor values('%1','%2','%3','%4','%5');"
                             ).arg(ID,Name,Achi,Credit,Type);
    QString strSQl2 = QString("insert into Teacher_Course (CourseID)"
                              " values('%1');").arg(ID);

    if(query.exec(strSql1)){
        if(query.exec(strSQl2)){
            QMessageBox::information(this,tr("success"),tr("添加课程成功。"));
            emit UpdateTable();
            return;
        }
    }
}

