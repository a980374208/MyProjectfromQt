#include "student.h"
#include "ui_student.h"

#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTimer>
#include "mainwindow.h"

CStudent::CStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CStudent)
{
    ui->setupUi(this);
    Init();
}

void CStudent::Init()
{
    setFixedSize(740,660);
    m_pModeUp = nullptr;
    m_pModeDown = nullptr;
    m_pChangePwDlg = nullptr;
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
        delete this;
    });

    QString sqlSelect = QString("select * from CourseInfor");
    SelectPublicCourse(sqlSelect);


    connect(this,&CStudent::UpDateTableView_2,this,&CStudent::On_UpdateTableView_2);
    QTimer::singleShot(0,this,&CStudent::On_InitFinished);
}

void CStudent::contextMenuEvent(QContextMenuEvent *event)
{
    m_ShortcutMenu->move(cursor().pos());
    m_ShortcutMenu->show();
}

CStudent::~CStudent()
{
    delete ui;
    delete m_pChangePwDlg;
}



void CStudent::ReciveDatabase(QSqlDatabase db,QString user,QString Password)
{
    m_Db = db;
    m_strUser = user;
    m_strPassword = Password;

}



void CStudent::on_comboBox_Select_currentIndexChanged(int index)
{
    if(index == 0){
        QString sqlSelect = QString("select * from CourseInfor");
        SelectPublicCourse(sqlSelect);
        return;
    }else if(index == 1){
        //嵌套查询查询到本专业的所有课程
        QString sqlSelect = QString("select * from CourseInfor where CourseID"
                                    " IN (select CourseID from Teacher_Course where TeacherID"
                                    " IN (select TeacherID from TeacherInfor"
                                    " where Belong = (select Belong from ClassInfor"
                                    " where ClassID = (select ClassID from StudentInfor"
                                    " where StudentID = '%1'))));"
                                    ).arg(m_strUser);
        SelectPublicCourse(sqlSelect);
        return;
    }else{

        QString sqlSelect = QString("select * from CourseInfor where CourseType = '%1';").arg(tr("elective"));
        SelectPublicCourse(sqlSelect);
        return;
    }
}

void CStudent::SelectPublicCourse(QString &str)
{
    if(!m_pModeUp)
        m_pModeUp  = new QSqlQueryModel(this);
   m_pModeUp->setQuery(str) ;
   m_pModeUp->setHeaderData(0,Qt::Horizontal,QObject::tr("CourseID"));
   m_pModeUp->setHeaderData(1,Qt::Horizontal,QObject::tr("CourseName"));
   m_pModeUp->setHeaderData(2,Qt::Horizontal,QObject::tr("Scheduling"));
   m_pModeUp->setHeaderData(3,Qt::Horizontal,QObject::tr("CourseCredit"));
   m_pModeUp->setHeaderData(4,Qt::Horizontal,QObject::tr("CourseType"));

    ui->tableView->setModel(m_pModeUp);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

}


void CStudent::on_pushButton_ConfirmSelect_clicked()
{
    if(ui->tableView->currentIndex().row() == -1){
        QMessageBox::warning(this,tr("error"),tr("please select a Course"));
        return;
    }
    if(QMessageBox::Yes ==QMessageBox::question(this," ",tr("if you realy wangt to select the Course?"))){
        //获取表格内课程号
        int row= ui->tableView->currentIndex().row();
        QAbstractItemModel *model = ui->tableView->model ();
        QModelIndex index = model->index(row,0);//选中行第一列的内容
        QVariant data = model->data(index);
        QString strClassID = data.toString();


        //通过课程号查询课程所属院系
        QString sqlSelcet1 = QString("select Belong from TeacherInfor where TeacherID"
                                     " = (select TeacherID from Teacher_Course where CourseID = '%1');").arg(strClassID);
        //通过学号查询学生所属院系
        QString sqlSelect2 = QString("select Belong from ClassInfor where ClassID"
                                     " = (select ClassID from StudentInfor where StudentId = '%1');").arg(m_strUser);
        QString aa;
        QString bb;
        if(query.exec(sqlSelcet1)){
            query.next();
            aa = query.value(0).toString();
        }
        if(query.exec(sqlSelect2)){
            query.next();
            bb = query.value(0).toString();
        }

        //判断是否为本专业课或选修课
        if(aa==bb||aa == tr("PublicCourse")){
            //判断是否已修本课程
            QString sqlSelect3 = QString("select CourseID from CourseRecord where StudentID = '%1';"
                                         ).arg(m_strUser);
            if(query.exec(sqlSelect3)){
                while(query.next()){
                    if(query.value(0)==strClassID){
                        QMessageBox::warning(this,tr("error"),tr("you was to seleced the Course"));
                        return;
                    }
                }
                QString sqlInsert = QString("INSERT INTO CourseRecord (StudentID,CourseID) VALUES ('%1','%2');"
                                            ).arg(m_strUser,strClassID);
                if(query.exec(sqlInsert)){
                    emit UpDateTableView_2();
                    QMessageBox::information(this,tr("succss"),tr("select the course succeed"));
                    return;
                }
            }
        }else{
            qDebug()<<"aaaaa="<<aa;
            QMessageBox::warning(this,tr("error"),tr("you selected the course is not your department or public department"));
        }
    }
}

void CStudent::On_InitFinished()
{
    emit UpDateTableView_2();

    QString strUserName;
    int sum = 0;
    //初始化欢迎标签
    ////qDebug()<<"m_strUser ="<<m_strUser;
    QString sqlSelect = QString("select StudentName from StudentInfor"
                                " where StudentID = '%1';").arg(m_strUser);
    query.exec(sqlSelect);
    if(query.next())
        strUserName = query.value(0).toString();
    ui->label_Welcome->setText(tr("%1 welcome to enter").arg(strUserName));
    //初始化总学分标签
    QString sqlSelect1 = QString("select CourseCredit from CourseInfor"
                                 " where CourseID IN (select CourseID from CourseRecord where StudentID = '%1');").arg(m_strUser);
    query.exec(sqlSelect1);
    while(query.next()){
        sum += query.value(0).toInt();
    }
    ui->label_Sum->setText(tr("Credits that have been completed: %1").arg(sum));
    return;
}

void CStudent::On_UpdateTableView_2()
{
    QString sqlSelect1 = QString("SELECT CourseRecord.CourseID,CourseInfor.CourseName , TeacherInfor.TeacherName, CourseInfor.CourseCredit,CourseRecord.Achievement"
                                 " FROM CourseRecord"
                                 " LEFT JOIN Teacher_Course"
                                 " ON CourseRecord.CourseID=Teacher_Course.CourseID"
                                 " LEFT JOIN TeacherInfor"
                                 " ON Teacher_Course.TeacherID = TeacherInfor.TeacherID"
                                 " LEFT JOIN CourseInfor"
                                 " ON Teacher_Course.CourseID = CourseInfor.CourseID"
                                 " where CourseRecord.StudentId = '%1'  and TeacherInfor.Permissions = '%2';").arg(m_strUser,tr("教师"));
    if(!m_pModeDown)
        m_pModeDown  = new QSqlQueryModel(this);
    m_pModeDown->setQuery(sqlSelect1);
    m_pModeDown->setHeaderData(0,Qt::Horizontal,QObject::tr("CourseID"));
    m_pModeDown->setHeaderData(1,Qt::Horizontal,QObject::tr("CourseName"));
    m_pModeDown->setHeaderData(2,Qt::Horizontal,QObject::tr("TeacherName"));
    m_pModeDown->setHeaderData(3,Qt::Horizontal,QObject::tr("CourseCredit"));
    m_pModeDown->setHeaderData(4,Qt::Horizontal,QObject::tr("Achievement"));
    ui->tableView_2->setModel(m_pModeDown);

    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    return;
}


void CStudent::on_pushButton_ConfirmExit_clicked()
{
    if(ui->tableView_2->currentIndex().row() == -1){
        QMessageBox::warning(this,tr("error"),tr("please select a Course"));
        return;
    }
    QVariant data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),4));
    QString strStudentAchievement = data.toString();
    if(!strStudentAchievement.isEmpty()){
        QMessageBox::critical(this,tr("error"),tr("Because of you was have the achievemrnt so you can't withdraw from this course"));
        return;
    }
    int status = QMessageBox::question(this,"",tr("If you realy wang to cancel the course?"));
    if(status == QMessageBox::Yes){
       QString CourseID = ui->tableView_2->model()->data(ui->tableView_2->model()->index(ui->tableView_2->currentIndex().row(),0)).toString();
       QString sqlDelete = QString("DELETE FROM CourseRecord"
                                   " WHERE StudentID='%1' AND CourseID='%2';").arg(m_strUser,CourseID);
       if(query.exec(sqlDelete)){
           emit UpDateTableView_2();
           QMessageBox::information(this,tr("success"),tr("cancel the course successed"));
           return;
       }

    }else{
        return;
    }
}


void CStudent::on_pushButtonChangePassword_clicked()
{
    if(m_pChangePwDlg){
        m_pChangePwDlg->show();
        return;
    }

    m_pChangePwDlg = new CDialog_ChangePassword(this);
    connect(this,&CStudent::SendUser,m_pChangePwDlg,&CDialog_ChangePassword::ReciveUser);
    emit SendUser(m_strUser,0);
    m_pChangePwDlg->show();
}

