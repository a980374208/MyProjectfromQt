#include "teachermanger.h"
#include "ui_teachermanger.h"
#include <QTimer>
#include <QMessageBox>
#include <QDebug>



CTeacherManger::CTeacherManger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CTeacherManger)
{
    ui->setupUi(this);
    m_pMode = nullptr;
    m_pAppointTable = nullptr;
    m_pAddTeacherDialog = nullptr;
    m_nNumforCourse = 0;
    m_nNumforClass = 0;



    ui->pushButton_CancelCoun->setEnabled(false);


   m_strSqlTeacher = QString ("select TeacherInfor.TeacherID,TeacherInfor.TeacherName,CourseInfor.CourseName,CourseInfor.CourseID,TeacherInfor.Belong,TeacherInfor.Permissions"
                               " from TeacherInfor"
                               " Left join Teacher_Course"
                               " on TeacherInfor.TeacherID = Teacher_Course.TeacherID"
                               " left join CourseInfor"
                               " on Teacher_Course.CourseID = CourseInfor.CourseID"
                               " Where TeacherInfor.Permissions = '%1'"
                               " order by TeacherInfor.TeacherID"
                               ).arg(tr("教师"));
   m_strSqlCounselor = QString ("select TeacherInfor.TeacherID,TeacherInfor.TeacherName,ClassInfor.ClassID,ClassInfor.ClassName,TeacherInfor.Belong,TeacherInfor.Permissions"
                                " from TeacherInfor"
                                " Left join Teacher_Course , ClassInfor"
                                " on TeacherInfor.TeacherID = Teacher_Course.TeacherID and ClassInfor.TeacherID = TeacherInfor.TeacherID"
                                " left join CourseInfor"
                                " on Teacher_Course.CourseID = CourseInfor.CourseID"
                                " Where TeacherInfor.Permissions = '%1';").arg(tr("辅导员"));
   m_strSqlNoCounselorClass = QString ("select ClassID,ClassName,Belong,TeacherID"
                                       " from ClassInfor where TeacherID is null;");
   m_strSqlNoTeacherCourse = QString ("select CourseID,CourseName,Scheduling,CourseCredit,CourseType"
                                      " From CourseInfor"
                                      " where CourseID in (select CourseID from Teacher_Course where TeacherID is null);");

   QTimer::singleShot(0,this,&CTeacherManger::ON_SLOT_Finished);
}

CTeacherManger::~CTeacherManger()
{
    delete ui;
}
void CTeacherManger::ReciveDatabase(QSqlDatabase db, QString user, QString Password)
{
    m_Db = db;
    m_strUser = user;
    m_strPassword = Password;
}

void CTeacherManger::ON_SLOT_Finished()
{

    ShowSelectInfor(m_strSqlTeacher);
}

void CTeacherManger::ShowSelectInfor(QString &str,DISPLAYTYPE type)
{
    if(!m_pMode)
        m_pMode  = new QSqlQueryModel(this);
    m_pMode->setQuery(str);
    if(type == DISPLAYTYPE::TEACHER||type == DISPLAYTYPE::COUNSELOR){
            m_pMode->setHeaderData(0,Qt::Horizontal,QObject::tr("TeacherID"));
            m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("TeacherName"));
            m_pMode->setHeaderData(2,Qt::Horizontal,QObject::tr("CourseName"));
            m_pMode->setHeaderData(3,Qt::Horizontal,QObject::tr("CourseID"));
            m_pMode->setHeaderData(4,Qt::Horizontal,QObject::tr("Belong"));
            m_pMode->setHeaderData(5,Qt::Horizontal,QObject::tr("Permissions"));
        //    m_pMode->setHeaderData(6,Qt::Horizontal,QObject::tr("CourseName"));
        //    m_pMode->setHeaderData(7,Qt::Horizontal,QObject::tr("Scheduling"));
        //    m_pMode->setHeaderData(8,Qt::Horizontal,QObject::tr("CourseCredit"));
        //    m_pMode->setHeaderData(9,Qt::Horizontal,QObject::tr("CourseType"));
        //    m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("Achievement"));
        //    m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("StartTime"));
        //    m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("HomeAdr"));

    }else if(type == DISPLAYTYPE::NOCOUNSELORCLASS){
        m_pMode->setHeaderData(0,Qt::Horizontal,QObject::tr("ClassID"));
        m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("ClassName"));
        m_pMode->setHeaderData(2,Qt::Horizontal,QObject::tr("Belong"));
        m_pMode->setHeaderData(3,Qt::Horizontal,QObject::tr("TeacherID"));

    }else if(type == DISPLAYTYPE::NOTEACHERCOURSE){
        m_pMode->setHeaderData(0,Qt::Horizontal,QObject::tr("CourseID"));
        m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("CourseName"));
        m_pMode->setHeaderData(2,Qt::Horizontal,QObject::tr("Scheduling"));
        m_pMode->setHeaderData(3,Qt::Horizontal,QObject::tr("CourseCredit"));
        m_pMode->setHeaderData(4,Qt::Horizontal,QObject::tr("CourseType"));

    }

    ui->tableView->setModel(m_pMode);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->show();
}

void CTeacherManger::GetSelectItemText(QString &ID,int index)
{
    QVariant Id = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),index));
    //QVariant Permissions = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5));
    ID = Id.toString();
    //Preimissions = Permissions.toString();
}

void CTeacherManger::on_pushButton_clicked()
{


}


void CTeacherManger::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        ui->pushButton_AppointCoun->setEnabled(true);
        ui->pushButton_AppointCour->setEnabled(true);
        ui->pushButton_CancelCoun->setEnabled(false);
        ui->pushButton_CancelCour->setEnabled(true);
        ui->pushButton_AddTeacher->setEnabled(true);
        ui->pushButton_DelTeacher->setEnabled(true);
        ShowSelectInfor(m_strSqlTeacher);
    }else if(index == 1){
        ui->pushButton_AppointCoun->setEnabled(false);
        ui->pushButton_AppointCour->setEnabled(false);
        ui->pushButton_CancelCoun->setEnabled(true);
        ui->pushButton_CancelCour->setEnabled(false);
        ui->pushButton_AddTeacher->setEnabled(false);
        ui->pushButton_DelTeacher->setEnabled(false);
        ShowSelectInfor(m_strSqlCounselor,DISPLAYTYPE::COUNSELOR);
    }else if(index == 2){
        ui->pushButton_AppointCoun->setEnabled(false);
        ui->pushButton_AppointCour->setEnabled(false);
        ui->pushButton_CancelCoun->setEnabled(false);
        ui->pushButton_CancelCour->setEnabled(false);
        ui->pushButton_AddTeacher->setEnabled(false);
        ui->pushButton_DelTeacher->setEnabled(false);
        ShowSelectInfor(m_strSqlNoCounselorClass,DISPLAYTYPE::NOCOUNSELORCLASS);
    }else if(index == 3){
        ui->pushButton_AppointCoun->setEnabled(false);
        ui->pushButton_AppointCour->setEnabled(false);
        ui->pushButton_CancelCoun->setEnabled(false);
        ui->pushButton_CancelCour->setEnabled(false);
        ui->pushButton_AddTeacher->setEnabled(false);
        ui->pushButton_DelTeacher->setEnabled(false);
        ShowSelectInfor(m_strSqlNoTeacherCourse,DISPLAYTYPE::NOTEACHERCOURSE);
    }
}


void CTeacherManger::on_pushButton_AppointCoun_clicked()
{
    if(!ui->tableView->selectionModel()->hasSelection()){
        QMessageBox::warning(this,tr("error"),tr("you don't selected any row"));
        return;
    }
    QString SelectedID;
    GetSelectItemText(SelectedID,0);
    QString strSqlSele = QString("select Permissions from TeacherInfor where TeacherID = '%1'").arg(SelectedID);
    m_query.exec(strSqlSele);
    while(m_query.next()){
        if(m_query.value(0).toString() == tr("辅导员")){
            QMessageBox::warning(this,tr("error"),tr("you selected teacher was coun"));
            return;
        }
    }

    if(!m_pAppointTable)
        m_pAppointTable = new CDialog_AppointTable;
    if(m_nNumforClass == 0){
        connect(this,&CTeacherManger::SendsqlNoCounClass,m_pAppointTable,&CDialog_AppointTable::ON_SLOT_ReciveNoCounClass);
        connect(this,&CTeacherManger::SendID,m_pAppointTable,&CDialog_AppointTable::ON_SLOT_ReciverID);
        m_nNumforClass+=1;
    }

    emit SendsqlNoCounClass(m_strSqlNoCounselorClass);

    emit SendID(SelectedID);
    m_pAppointTable->setModal(true);
    m_pAppointTable->show();
}


void CTeacherManger::on_pushButton_CancelCoun_clicked()
{
    if(!ui->tableView->selectionModel()->hasSelection()){
        QMessageBox::warning(this,tr("error"),tr("you don't selected any row"));
        return;
    }
    int button = QMessageBox::question(this,tr("取消导员"),tr("您是否确认要取消选中导员的导员身份？"));
    if(button == QMessageBox::No)
        return;
    QString SelectedTeacherID;
    GetSelectItemText(SelectedTeacherID,0);
    QString SelectedClassID;
    GetSelectItemText(SelectedClassID,2);
    QString strsql = QString("DELETE FROM TeacherInfor"
                             " WHERE TeacherID = '%1' and Permissions = '%2';").arg(SelectedTeacherID,tr("辅导员"));
    QString strSql1 = QString("update ClassInfor"
                             " set TeacherID = NULL"
                             " where ClassID = '%1' and TeacherID = '%2'").arg(SelectedClassID,SelectedTeacherID);
    qDebug()<<"bbbbbb"<<SelectedClassID<<SelectedTeacherID;
    if(m_query.exec(strsql)){
        if(m_query.exec(strSql1)){
            ShowSelectInfor(m_strSqlCounselor,DISPLAYTYPE::COUNSELOR);
            QMessageBox::information(this,tr("success"),tr("取消选中导员,导员身份成功，请尽快为改班级安排新的导员。"));
            return;
        }
    }
}


void CTeacherManger::on_pushButton_AppointCour_clicked()
{
    if(!ui->tableView->selectionModel()->hasSelection()){
        QMessageBox::warning(this,tr("error"),tr("you don't selected any row"));
        return;
    }

    QString SelectedID;
    GetSelectItemText(SelectedID,0);

    if(!m_pAppointTable){
        m_pAppointTable = new CDialog_AppointTable;

    }
    if(m_nNumforCourse == 0){
        connect(this,&CTeacherManger::SendsqlNoCounClass,m_pAppointTable,&CDialog_AppointTable::ON_SLOT_ReciveNoTeaCourse);
        connect(this,&CTeacherManger::SendID,m_pAppointTable,&CDialog_AppointTable::ON_SLOT_ReciverID);
        connect(m_pAppointTable,&CDialog_AppointTable::UpdateView,this,[=](){
        ShowSelectInfor(m_strSqlTeacher);
        });
        m_nNumforCourse+=1;
    }
    emit SendID(SelectedID);
    emit SendsqlNoCounClass(m_strSqlNoTeacherCourse);
    m_pAppointTable->setModal(true);
    m_pAppointTable->show();
}


void CTeacherManger::on_pushButton_CancelCour_clicked()
{
    if(!ui->tableView->selectionModel()->hasSelection()){
        QMessageBox::warning(this,tr("error"),tr("you don't selected any row"));
        return;
    }
    int button = QMessageBox::question(this,tr("取消课程"),tr("您是否确认要取消选中教师此课程教师身份？"));
    if(button == QMessageBox::No)
        return;
    if(button == QMessageBox::Yes){
        QString SelectedID;
        GetSelectItemText(SelectedID,0);
        QString CourseID;
        GetSelectItemText(CourseID,3);
        QString strSql = QString("update Teacher_Course "
                                 " set TeacherID = NULL"
                                 " where CourseId = '%1' and TeacherID = '%2';").arg(CourseID,SelectedID);
        if(m_query.exec(strSql)){
            ShowSelectInfor(m_strSqlTeacher,DISPLAYTYPE::TEACHER);
            QMessageBox::information(this,tr("success"),tr("取消选中教师及课程，此课程教师身份成功，请尽快安排新的教师。"));
            return;
        }
    }


}


void CTeacherManger::on_pushButton_AddTeacher_clicked()
{
    if(!m_pAddTeacherDialog){
        m_pAddTeacherDialog = new CDialog_AddTeacher;
        connect(m_pAddTeacherDialog,&CDialog_AddTeacher::SendUpdate,this,[=](){
            ShowSelectInfor(m_strSqlTeacher);
        });
    }
    m_pAddTeacherDialog->show();
}


void CTeacherManger::on_pushButton_DelTeacher_clicked()
{
    QString TeacherID;
    GetSelectItemText(TeacherID,0);
    QString strSql = QString("select TeacherID from Teacher_Course where TeacherID = '%1'").arg(TeacherID);
    m_query.exec(strSql);
    if(m_query.next()){
        QMessageBox::warning(this,tr("error"),tr("您选择的教师还有任职的课程取消该教师全部任职课程后再删除。"));
        return;
    }
    QString strSql2 = QString("DELETE FROM TeacherInfor"
                              " WHERE TeacherID = '%1' and Permissions = '%2';").arg(TeacherID,tr("教师"));
    QString strSql3 = QString("select TeacherID from TeacherInfor where TeacherID = '%1'").arg(TeacherID);
    m_query.exec(strSql3);
    if(m_query.next()){
       m_query.exec(strSql2);
       ShowSelectInfor(m_strSqlTeacher);
       QMessageBox::information(this,tr("success"),tr("删除教师成功"));
    }else{
        QString strSql4 = QString("DELETE FROM Password"
                                  " WHERE TeacherID = '%1'").arg(TeacherID);
        m_query.exec(strSql2);
        m_query.exec(strSql4);
        ShowSelectInfor(m_strSqlTeacher);
        QMessageBox::information(this,tr("success"),tr("删除教师成功"));
    }
    return;
}

