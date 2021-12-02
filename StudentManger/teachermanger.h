#ifndef TEACHERMANGER_H
#define TEACHERMANGER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <dialog_appointtable.h>
#include <dialog_addteacher.h>

enum class DISPLAYTYPE{
    TEACHER = 0,
    COUNSELOR = 1,
    NOCOUNSELORCLASS = 2,
    NOTEACHERCOURSE = 3
};

namespace Ui {
class CTeacherManger;
}

class CTeacherManger : public QMainWindow
{
    Q_OBJECT

signals:
    void SendsqlNoCounClass(QString &a);

    void SendsqlNoTeaCourse(QString &a);

    void SendID(QString a);

public slots:
     void ReciveDatabase(QSqlDatabase db,QString user,QString Password);

private slots:

     void ON_SLOT_Finished();

     void on_pushButton_clicked();

     void on_comboBox_currentIndexChanged(int index);

     void on_pushButton_AppointCoun_clicked();

     void on_pushButton_CancelCoun_clicked();

     void on_pushButton_AppointCour_clicked();

     void on_pushButton_CancelCour_clicked();

     void on_pushButton_AddTeacher_clicked();

     void on_pushButton_DelTeacher_clicked();

public:
    explicit CTeacherManger(QWidget *parent = nullptr);
    ~CTeacherManger();

private:
     void ShowSelectInfor(QString &str,DISPLAYTYPE type = DISPLAYTYPE::TEACHER);

     void GetSelectItemText(QString &ID,int index);

private:
    Ui::CTeacherManger *ui;
    QSqlDatabase         m_Db;
    QString              m_strUser;
    QString              m_strPassword;
    QSqlQuery            m_query;
    QSqlQueryModel*       m_pMode;
    QString               m_strSqlTeacher;
    QString               m_strSqlCounselor;
    QString               m_strSqlNoCounselorClass;
    QString               m_strSqlNoTeacherCourse;
    CDialog_AppointTable* m_pAppointTable;
    int                   m_nNumforCourse;
    int                   m_nNumforClass;

    CDialog_AddTeacher*   m_pAddTeacherDialog;
};

#endif // TEACHERMANGER_H
