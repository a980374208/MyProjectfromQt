#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMenu>
#include <modifyedachidialog.h>
#include <dialog_changepassword.h>

enum class IDSAVE{
    SAVE = 0,
    NOTSAVE = 1
};
enum class SHOWTYPE{
    EASY = 0,
    ALL = 1
};



namespace Ui {
class CTeacher;
}

class CTeacher : public QWidget
{
    Q_OBJECT
signals:
    void SendDatabase(QSqlDatabase &db,QString user,QString sqlSel);
    void SendUser(QString user,int role);
public slots:
     void ReciveDatabase(QSqlDatabase db,QString user,QString Password);
     void ON_ChangeToAdmin();
protected:
    virtual void  contextMenuEvent ( QContextMenuEvent * event );

private slots:
     void ON_SLOT_InitFinished();

     void ON_SLOT_UpdateTable();

     void on_comboBox_TeacherPower_currentIndexChanged(int index);


     void on_checkBox_stateChanged(int arg1);

     void on_pushButton_Select_clicked();

     void on_comboBox_Select_currentIndexChanged(int index);

     void on_pushButton_StartSort_clicked();

     void on_pushButton_ModiftedAchi_clicked();

     void on_pushButton_Disqualification_clicked();

     void on_pushButton_ChangePassword_clicked();

public:
    explicit CTeacher(QWidget *parent = nullptr);
    ~CTeacher();
private:
     void Init();
     void ShowSelectInfor(QString& str,SHOWTYPE type = SHOWTYPE::EASY,IDSAVE issave = IDSAVE::SAVE);


private:
    Ui::CTeacher *ui;
public:
    QSqlDatabase         m_Db;
    QString              m_strUser;
    QString              m_strPassword;
    QSqlQueryModel*      m_pMode;
    QSqlQuery            query;
    QMenu*               m_ShortcutMenu;
    CModifyedAchiDialog* m_pDlg;
    CDialog_ChangePassword* m_pChangePwDlg;
    QString              m_strSqlSelectMystudentEasy;
    QString              m_strSqlSelectMystudentAll;
    QString              m_strSqlSelectManagerstudentEasy;
    QString              m_strSqlSelectManagerstudentAll;
    QString              m_strSqlSelectLast;
    bool                 m_Admin;
};

#endif // TEACHER_H
