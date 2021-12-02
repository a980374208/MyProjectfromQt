#include "dialog_addteacher.h"
#include "ui_dialog_addteacher.h"
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
CDialog_AddTeacher::CDialog_AddTeacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialog_AddTeacher)
{
    ui->setupUi(this);
    QRegExp rx("[0-9]{5}");
    ui->lineEdit_ID->setValidator(new QRegExpValidator(rx, this));
    QRegExp rx1("^[\\一-\\龥]{0,}$");
    ui->lineEdit_Nanme->setValidator(new QRegExpValidator(rx1, this));
    ui->lineEdit_Nanme->setMaxLength(5);
}

CDialog_AddTeacher::~CDialog_AddTeacher()
{
    delete ui;

}

void CDialog_AddTeacher::on_pushButton_OK_clicked()
{
    if(ui->lineEdit_ID->text().isEmpty()||ui->lineEdit_Nanme->text().isEmpty()){
        QMessageBox::warning(this,tr("error"),tr("ID 和姓名不能为空"));
        return;
    }
    if(ui->lineEdit_ID->text().length()<5){
        QMessageBox::warning(this,tr("error"),tr("ID必须为5位数且都是数字"));
        return;
    }
    QString ID = ui->lineEdit_ID->text();
    QString Name = ui->lineEdit_Nanme->text();
    QString Department = ui->comboBox->currentText();
    QString Permissions = QString(tr("教师"));
    QString strSql = QString("select TeacherID from TeacherInfor where TeacherID = '%1'").arg(ID);
    QSqlQuery query;
    query.exec(strSql);
    if(query.next()){
        QMessageBox::warning(this,tr("error"),tr("已经存在该教师ID"));
        return;
    }
    QString strSql1 = QString("insert into TeacherInfor(TeacherID,TeacherName,Belong,Permissions)"
                              " values('%1','%2','%3','%4');").arg(ID,Name,Department,Permissions);
    QString strSql2 = QString("insert into Password(USerID,Password) values('%1','123456')").arg(ID);
    if(query.exec(strSql1)){
        if(query.exec(strSql2)){
            QMessageBox::information(this,tr("success"),tr("添加教师成功,初始密码为123456"));
            emit SendUpdate();
        }
    }
}

void CDialog_AddTeacher::reject()
{
    ui->lineEdit_ID->clear();
    ui->lineEdit_Nanme->clear();
    QDialog::reject();

}

