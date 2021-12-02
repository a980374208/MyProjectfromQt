#include "admin.h"
#include "ui_admin.h"

#include <QDebug>
#include <QMessageBox>
#include "mainwindow.h"

void CAdmin::contextMenuEvent(QContextMenuEvent *event)
{
    m_ShortcutMenu->move(cursor().pos());
    m_ShortcutMenu->show();
}

CAdmin::CAdmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CAdmin)
{
    ui->setupUi(this);
    m_pTeacher = nullptr;
    m_pChangePwDlg = nullptr;
    m_pMangerTeacher = nullptr;
    m_pMangerCourse = nullptr;
    m_ShortcutMenu    = new QMenu(this);
    QAction* m_exitAction  = new QAction(tr("exit"),this);
    QAction* m_LogoutAction = new QAction(tr("Logout"),this);
    m_ShortcutMenu->addAction(m_exitAction);
    m_ShortcutMenu->addAction(m_LogoutAction);
    connect(m_exitAction,&QAction::triggered,this,[=](){
        this->close();
    });
    connect(m_LogoutAction,&QAction::triggered,this,[=](){
        MainWindow* mainWain = new MainWindow;

        mainWain->show();
        delete  this;

    });
}

CAdmin::~CAdmin()
{
    delete ui;
    delete m_pTeacher;
    delete m_pChangePwDlg;
    delete m_pMangerTeacher;
    delete m_pMangerCourse;
}

void CAdmin::ReciveDatabase(QSqlDatabase db, QString user, QString Password)
{
    m_Db = db;
    m_strUser = user;
    m_strPassword = Password;
}

void CAdmin::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->deleteLater();
}

void CAdmin::on_pushButton_StudentManger_clicked()
{
    if(!m_pTeacher)
        m_pTeacher = new CTeacher();
    connect(this,&CAdmin::SendDatabase,m_pTeacher,&CTeacher::ReciveDatabase);
    emit SendDatabase(m_Db,m_strUser,m_strPassword);
    connect(this,&CAdmin::ChangeToAdmin,m_pTeacher,&CTeacher::ON_ChangeToAdmin);
    emit ChangeToAdmin();
    m_pTeacher->show();
}



void CAdmin::on_pushButton_TeacherManger_clicked()
{
    if(m_pMangerTeacher){
        m_pMangerTeacher->show();
        return;
    }

    m_pMangerTeacher = new CTeacherManger(this);
    connect(this,&CAdmin::SendDatabase,m_pMangerTeacher,&CTeacherManger::ReciveDatabase);
    emit SendDatabase(m_Db,m_strUser,m_strPassword);

    m_pMangerTeacher->show();

}


void CAdmin::on_pushButton_ChangePassword_clicked()
{
    if(m_pChangePwDlg){
        m_pChangePwDlg->show();
        return;
    }

    m_pChangePwDlg = new CDialog_ChangePassword(this);
    connect(this,&CAdmin::SendUser,m_pChangePwDlg,&CDialog_ChangePassword::ReciveUser);
    emit SendUser(m_strUser,2);
    m_pChangePwDlg->show();
}


void CAdmin::on_pushButton_CourseManger_clicked()
{
    if(m_pMangerCourse){
        m_pMangerCourse->show();
        return;
    }
    m_pMangerCourse = new CCourseManger(this);
    m_pMangerCourse->show();

}

