#include "dialog_register.h"
#include "ui_dialog_register.h"
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QDate>

CDialog_Register::CDialog_Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialog_Register)
{
    ui->setupUi(this);
    QRegExp rx("[0-9]{12}");
    QRegExp rx3("[0-9]{5}");
    ui->lineEdit_ID->setValidator(new QRegExpValidator(rx, this));
    QRegExp rx1("^[\\一-\\龥]{0,}$");
     QRegExp rx2("^150$|^(\\d|[1-9]\\d)(\\.\\d+)*$");
    ui->lineEdit_Name->setValidator(new QRegExpValidator(rx1, this));
    ui->lineEdit_Name->setMaxLength(10);
    ui->lineEdit_Age->setValidator(new QRegExpValidator(rx2, this));
    ui->lineEdit_Adr->setValidator(new QRegExpValidator(rx1, this));
    ui->lineEdit_CourseID->setValidator(new QRegExpValidator(rx3, this));

}

CDialog_Register::~CDialog_Register()
{
    delete ui;
}

void CDialog_Register::on_pushButton_OK_clicked()
{
    QDate currentdate = QDate::currentDate();
    QString str1 = currentdate.toString("yyyy-MM-dd");
    QByteArray ba = str1.toLatin1();//将QString 转换为 char *类型
    char *dateStr = ba.data();//将QString 转换为 char *类型
    char *year = strtok(dateStr,"-");

    QString StartTime = year;
    QString ID = ui->lineEdit_ID->text();
    QString Name = ui->lineEdit_Name->text();
    QString Age = ui->lineEdit_Age->text();

    QString ClassID = ui->lineEdit_CourseID->text();
    QString Adr = ui->lineEdit_Adr->text();
    QString Sex;

    if(ui->radioButton_Man->isChecked()){
        Sex = tr("男");
    }else{
        Sex = tr("女");
    }

    if(ID.isEmpty()||Name.isEmpty()||Age.isEmpty()||ClassID.isEmpty()||Adr.isEmpty()){
        QMessageBox::warning(this,tr("error"),tr("请把内容填写完整。"));
        return;
    }
    if(ID.length() != 12){
        QMessageBox::warning(this,tr("error"),tr("学生学号必须为12位数字。"));
        return;
    }
    QString strSql = QString("select * from StudentInfor where StudentID = '%1'").arg(ID);
    QSqlQuery query;
    query.exec(strSql);
    qDebug()<<strSql;
    if(query.next()){
        QMessageBox::warning(this,tr("error"),tr("该学生ID已存在."));
        return;
    }
    QString strSql2 = QString("select ClassID from ClassInfor where ClassID = '%1'").arg(ClassID);
    query.exec(strSql2);
    if(!query.next()){
        QMessageBox::warning(this,tr("error"),tr("不存在该班级ID."));
        return;
    }
    qDebug()<<ID<<Name<<StartTime<<Age<<Sex<<ClassID<<Adr;
    QString strSql3 = QString("insert into StudentInfor values "
                              "('%1','%2','%3','%4','%5','%6','%7')").arg(ID,Name,Sex,Age,StartTime,ClassID,Adr);
    QString strSql4 = QString("insert into Password values ('%1','123456')").arg(ID);
    if(query.exec(strSql3)){
        if(query.exec(strSql4)){
            QMessageBox::information(this,tr("success"),tr("注册成功初始密码为123456"));
            return;
        }
    }

}

