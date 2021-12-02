#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMenu>
#include <QAction>
#include "dialog_changepassword.h"

namespace Ui {
class CStudent;
}

class CStudent : public QWidget
{
    Q_OBJECT
signals:
    void UpDateTableView_2();
    void SendUser(QString user,int role);

public:
    explicit CStudent(QWidget *parent = nullptr);
    ~CStudent();
protected:
    virtual void  contextMenuEvent ( QContextMenuEvent * event );

private slots:
    void on_comboBox_Select_currentIndexChanged(int index);
    void on_pushButton_ConfirmSelect_clicked();
    //类创建完成后的初始化工作
    void On_InitFinished();
    //更新学生所修课程界面
    void On_UpdateTableView_2();

    void on_pushButton_ConfirmExit_clicked();

    void on_pushButtonChangePassword_clicked();

public slots:
    //接收登陆界面发送来的数据
    void ReciveDatabase(QSqlDatabase db,QString user,QString Password);



private:
    void Init();
    void SelectPublicCourse(QString &str);
private:
    Ui::CStudent *ui;
    QSqlDatabase       m_Db;
    QSqlQueryModel     *m_pModeUp;      //上方选课查询模型
    QSqlQueryModel     *m_pModeDown;    //下方查看所修课程和退课查询模型
    CDialog_ChangePassword* m_pChangePwDlg;


    QString            m_strUser;
    QString            m_strPassword;
    QSqlQuery          query;
    QMenu*             m_ShortcutMenu;

};

#endif // STUDENT_H
