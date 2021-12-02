#include "modifyedachidialog.h"
#include "ui_modifyedachidialog.h"
#include <QRegExpValidator>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

CModifyedAchiDialog::CModifyedAchiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CModifyedAchiDialog)
{
    ui->setupUi(this);
    QRegExp rx("[0-9]{12}");
    QRegExp rx1("[0-9]{3}");
    QRegExp rx2("^100$|^(\\d|[1-9]\\d)(\\.\\d+)*$");
    ui->lineEdit_CourseID->setValidator(new QRegExpValidator(rx1, this));
    ui->lineEdit_StudentID->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_StudentAchi->setValidator(new QRegExpValidator(rx2, this));
    setWindowTitle(tr("modifyed Achi"));


    QTimer::singleShot(0,this,&CModifyedAchiDialog::ON_SLOT_InitFinished);
}

CModifyedAchiDialog::~CModifyedAchiDialog()
{
    delete ui;
}

void CModifyedAchiDialog::ON_SLOT_InitFinished()
{
    m_strSqlSelectMystudentEasy = QString("select CourseRecord.StudentID,StudentInfor.StudentName,ClassInfor.ClassName,CourseInfor.CourseName,CourseInfor.CourseID,CourseInfor.CourseCredit,CourseRecord.Achievement"
                                 " from CourseRecord"
                                 " left join StudentInfor,CourseInfor"
                                 " on CourseRecord.StudentID = StudentInfor.StudentID and CourseRecord.CourseID = CourseInfor.CourseID"
                                 " left join ClassInfor"
                                 " on StudentInfor.ClassID = ClassInfor.ClassID"
                                 " where CourseRecord.CourseID in (select CourseID from Teacher_Course where TeacherID = '%1')").arg(m_strUser);
}

void CModifyedAchiDialog::on_pushButton_ok_clicked()
{
    QSqlQuery query;
    QString str = m_strSqlSelectManagerstudentEasy;
    QString str2 = m_strSqlSelectMystudentEasy;
    QString StuID = ui->lineEdit_StudentID->text();
    QString StuAchi = ui->lineEdit_StudentAchi->text();
    QString CouID = ui->lineEdit_CourseID->text();

    QString str3 = QString("  and CourseRecord.StudentID = '%1' and CourseRecord.CourseID = '%2';").arg(StuID,CouID);
    str.append(str3);
    str2.append(str3);

    query.exec(str);

    if(!query.next()){
        query.exec(str2);
        if(!query.next()){
         QMessageBox::warning(this,tr("error"),tr("you don't have this student as StudentID is %1 and CourseID is %2").arg(StuID,CouID));
         return;
        }
    }
    QString sql1 = QString("UPDATE CourseRecord SET Achievement = '%1' WHERE  StudentID = '%2' and CourseID = '%3';").arg(StuAchi,StuID,CouID);
    if(query.exec(sql1)){
        QMessageBox::information(this,tr("success"),tr("insert the achi succeed"));
        emit sendUpdate();
    }



}

void CModifyedAchiDialog::ReciveDatabase(QSqlDatabase &db, QString user,QString sqlSel)
{
    m_pDb = &db;
    m_strUser = user;
    m_strSqlSelectManagerstudentEasy = sqlSel;
}

void CModifyedAchiDialog::reject()
{
    ui->lineEdit_CourseID->clear();
    ui->lineEdit_StudentID->clear();
    ui->lineEdit_StudentAchi->clear();
    QDialog::reject();
}

