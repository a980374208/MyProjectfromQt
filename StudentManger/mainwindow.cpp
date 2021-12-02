#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "teacher.h"
#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>
#include <admin.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
    //qDebug()<<"len="<<strlen("where CourseRecord.CourseID in (select CourseID from Teacher_Course where TeacherID = '%1')");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pDiaRegister;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
            m_clickPos=event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
            move(event->pos()+pos()-m_clickPos);

}


void MainWindow::Init()
{

    m_pDiaRegister = nullptr;
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(), this->height());  //禁止拖动窗口大小
    setWindowFlags(Qt::FramelessWindowHint);
    m_Db = QSqlDatabase::addDatabase("QSQLITE");
    m_Db.setDatabaseName("studentmanger.db");
    if(!m_Db.open()){
        QMessageBox::warning(this,tr("error"),m_Db.lastError().text());
    }
    QRegExp rx("[0-9]{12}");
    ui->lineEdit_User->setValidator(new QRegExpValidator(rx, this));
    ui->lineEdit_Password->setMaxLength(16);
}

void MainWindow::SetInterfaceBg(QString &str)
{
     ui->frame->setStyleSheet(QString("*{background:rgb(255, 255, 255);font-size:15px;font-family:Century Gothic,sans-serif;}QFrame{border:sold 10px rgba(0,0,0);background-image:url(:/%1.png);}QLineEdit{color:#8d98a1;background-color:#405361;font-size:16px;border-style:outset;border-radius:10px;}QPushButton{background:#ced1d8;border-style:outset;border-radius:10px;}QPushButton:pressed{background-color:rgb(224,0,0);border-style:inset;}QRadioButton{background:rgba(85,170,255,0);color:white;}QLabel{background:rgba(85,170,255,0);color:white;font-style:italic bold;font-size:14px;}").arg(str));
}


void MainWindow::on_radioButton_Student_toggled(bool checked)
{
    if(checked == 1){
        ui->pushButton_Register->setEnabled(1);
        ui->pushButton_Login->setEnabled(1);
    }
    QString str = "2222";
    SetInterfaceBg(str);
}


void MainWindow::on_radioButton_Teacher_toggled(bool checked)
{
    if(checked == 1){
        ui->pushButton_Register->setEnabled(0);
        ui->pushButton_Login->setEnabled(1);
    }
    QString str = "1111";
    SetInterfaceBg(str);
}




void MainWindow::on_radioButton_Admin_toggled(bool checked)
{
    if(checked == 1){
        ui->pushButton_Register->setEnabled(0);
        ui->pushButton_Login->setEnabled(1);
    }

    QString str = "1111";
    SetInterfaceBg(str);
}


void MainWindow::on_pushButton_Close_clicked()
{
    close();
    delete this;
}


void MainWindow::on_pushButton_Login_clicked()
{
    if(ui->lineEdit_Password->text().isEmpty()||ui->lineEdit_User->text().isEmpty()){
        QMessageBox::information(this,tr("warning"),tr("please user and password cond't empty"));
        return;
    }
    QSqlQuery query;
    m_strUser = ui->lineEdit_User->text();
    m_strPassword = ui->lineEdit_Password->text();
    if(ui->radioButton_Student->isChecked()){
        QString sqlSelect = QString("select StudentInfor.StudentID,Password.Password"
                                    " from Password"
                                    " left join StudentInfor"
                                    " on Password.UserID = StudentInfor.StudentID"
                                    " where StudentInfor.StudentID = '%1' and Password.Password = '%2';"
                                    ).arg(m_strUser,m_strPassword);
        query.exec(sqlSelect);
        if(!query.next()){
            QMessageBox::warning(this,tr("warninig"),tr("账号或密码错误"));
            return;
        }
        CStudent* pStudent = new CStudent;
        connect(this,&MainWindow::SendDatabase,pStudent,&CStudent::ReciveDatabase);
        emit SendDatabase(m_Db,m_strUser,m_strPassword);
        pStudent->show();

        this->close();
        return;

    }else if(ui->radioButton_Teacher->isChecked()){
        QString sqlSelect = QString("select TeacherInfor.TeacherID,Password.Password"
                                    " from Password"
                                    " left join TeacherInfor"
                                    " on Password.UserID = TeacherInfor.TeacherID"
                                    " where TeacherInfor.TeacherID = '%1' and Password.Password = '%2'"
                                    ).arg(m_strUser,m_strPassword);
        query.exec(sqlSelect);
        if(!query.next()){
            QMessageBox::warning(this,tr("warninig"),tr("账号或密码错误"));
            return;
        }
        CTeacher* pTeacher = new CTeacher;
        connect(this,&MainWindow::SendDatabase,pTeacher,&CTeacher::ReciveDatabase);
        emit SendDatabase(m_Db,m_strUser,m_strPassword);
        pTeacher->show();

        this->close();
        return;

    }else if(ui->radioButton_Admin->isChecked()){
        QString sqlSelect = QString("select TeacherInfor.TeacherID,Password.Password"
                                    " from Password"
                                    " left join TeacherInfor"
                                    " on Password.UserID = TeacherInfor.TeacherID"
                                    " where TeacherInfor.TeacherID = '%1' and Password.Password = '%2'"
                                    ).arg(m_strUser,m_strPassword);
        query.exec(sqlSelect);
        if(!query.next()){
            QMessageBox::warning(this,tr("warninig"),tr("账号或密码错误"));
            return;
        }
        QString sqlSelect1 = QString("select Permissions from TeacherInfor where TeacherID = '%1';").arg(m_strUser);
        if(!query.exec(sqlSelect1))
            return;
        while(query.next()){
            if(query.value(0).toString() == tr("管理员")){
                CAdmin* pAdmin = new CAdmin;
                connect(this,&MainWindow::SendDatabase,pAdmin,&CAdmin::ReciveDatabase);
                emit SendDatabase(m_Db,m_strUser,m_strPassword);
                pAdmin->show();
                this->close();
                return;
            }
        }
        QMessageBox::warning(this,tr("error"),tr("this user isn't was admin"));
        return;
   }
}


void MainWindow::on_pushButton_Register_clicked()
{
    if(m_pDiaRegister){
        m_pDiaRegister->show();
        return;
    }
    m_pDiaRegister = new CDialog_Register(this);
    m_pDiaRegister->show();
}

