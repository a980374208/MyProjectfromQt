#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "teacher.h"
#include "dialog_changepassword.h"
#include "teachermanger.h"
#include "coursemanger.h"
#include <QMenu>

namespace Ui {
class CAdmin;
}

class CAdmin : public QMainWindow
{
    Q_OBJECT
signals:
    void SendDatabase(QSqlDatabase db,QString user,QString Password);
    void ChangeToAdmin();
    void SendUser(QString user,int role);

protected:
    virtual void  contextMenuEvent ( QContextMenuEvent * event );

public:
    explicit CAdmin(QWidget *parent = nullptr);
    ~CAdmin();
public slots:
     void ReciveDatabase(QSqlDatabase db,QString user,QString Password);

private slots:
    void on_pushButton_StudentManger_clicked();

    void on_pushButton_TeacherManger_clicked();

    void on_pushButton_ChangePassword_clicked();

    void on_pushButton_CourseManger_clicked();

private:
    Ui::CAdmin *ui;
    QSqlDatabase             m_Db;
    QMenu*                   m_ShortcutMenu;
    QString                  m_strUser;
    QString                  m_strPassword;
    CTeacher*                m_pTeacher;
    CDialog_ChangePassword*  m_pChangePwDlg;
    CTeacherManger*          m_pMangerTeacher;
    CCourseManger*           m_pMangerCourse;
};

#endif // ADMIN_H
