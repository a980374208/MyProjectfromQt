#include "dialog_changepassword.h"
#include "ui_dialog_changepassword.h"
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>



CDialog_ChangePassword::CDialog_ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialog_ChangePassword)
{
    ui->setupUi(this);
    setWindowTitle(tr("Change Password"));
    ui->lineEdit_New->setMaxLength(16);
    ui->lineEdit_Old->setMaxLength(16);
    ui->lineEdit_ConfirmNew->setMaxLength(16);

    QTimer::singleShot(0,this,&CDialog_ChangePassword::ON_InitFinshied);
}

void CDialog_ChangePassword::ReciveUser(QString user, int role)
{
    m_srUser = user;
    m_Father = role;
}

void CDialog_ChangePassword::ON_InitFinshied()
{

}

CDialog_ChangePassword::~CDialog_ChangePassword()
{
    delete ui;
}

void CDialog_ChangePassword::on_pushButton_ConfirmChange_clicked()
{
    QSqlQuery query;
    QString str;
    QString old;
    QString strold = ui->lineEdit_Old->text();
    QString strNew = ui->lineEdit_New->text();
    QString strConfirmNew = ui->lineEdit_ConfirmNew->text();
    if(strNew != strConfirmNew){
        QMessageBox::warning(this,tr("error"),tr("The passwords are inconsistent!"));
        return;
    }
    if(m_Father == 0){
        str = QString("select Password from Password where UserID = '%1'").arg(m_srUser);
    }else if(m_Father == 1){
        str = QString("select Password from Password where UserID = '%1'").arg(m_srUser);
    }else if(m_Father == 2){
        str = QString("select Password from Password where UserID = '%1'").arg(m_srUser);
    }
    query.exec(str);
    query.next();
    old = query.value(0).toString();
    if(old != strold){
        QMessageBox::warning(this,tr("error"),tr("old password is wrong!"));
        return;
    }

    if(m_Father == 0){

        QString sqlUpdate = QString("update Password set  Password = '%1'  where UserID = '%2'").arg(strConfirmNew,m_srUser);
        if(query.exec(sqlUpdate)){
            QMessageBox::information(this,tr("success"),tr("change the Password succeed."));
            return;
        }
    }else if(m_Father == 1||m_Father == 2){
        qDebug()<<"m_Father == "<<m_srUser;
        QString sqlUpdate = QString("update Password set  Password = '%1'  where UserID = '%2'").arg(strConfirmNew,m_srUser);
        if(query.exec(sqlUpdate)){
            QMessageBox::information(this,tr("success"),tr("change the Password succeed."));

            return;
        }
    }/*else if(m_Father == 2){
        QString sqlUpdate = QString("update Password set  Password = '%1'  where UserID = '%2'").arg(strConfirmNew,m_srUser);
        if(query.exec(sqlUpdate)){
            QMessageBox::information(this,tr("success"),tr("change the Password succeed."));
            return;
    }*/
}

void CDialog_ChangePassword::reject()
{
    ui->lineEdit_New->clear();
    ui->lineEdit_Old->clear();
    ui->lineEdit_ConfirmNew->clear();
    QDialog :: reject();
}

