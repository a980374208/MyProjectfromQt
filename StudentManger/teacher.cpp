#include "teacher.h"
#include "ui_teacher.h"
#include <QtDebug>
#include <QTimer>
#include "mainwindow.h"
#include <QRegExpValidator>
#include <QMessageBox>


CTeacher::CTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTeacher)
{
    ui->setupUi(this);
    setMinimumSize(935,640);
    m_pMode = nullptr;
    m_pDlg = nullptr;
    m_pChangePwDlg = nullptr;
    m_Admin = false;

    Init();

}
void CTeacher::ReciveDatabase(QSqlDatabase db, QString user, QString Password)
{
    m_Db = db;
    m_strUser = user;
    m_strPassword = Password;

}

void CTeacher::ON_ChangeToAdmin()
{
    m_Admin = true;
    ui->comboBox_TeacherPower->setItemText(0,tr("Manager's Student"));
//    ui->comboBox_TeacherPower->setItemData(1,tr(""),Qt::UserRole-1);
    setContextMenuPolicy(Qt::NoContextMenu);
}

void CTeacher::contextMenuEvent(QContextMenuEvent *event)
{
    m_ShortcutMenu->move(cursor().pos());
    m_ShortcutMenu->show();
}

void CTeacher::ON_SLOT_InitFinished()
{

    QString TeacherName;
    QString strSelect = QString ("select TeacherName from TeacherInfor where TeacherID = '%1'").arg(m_strUser);
    query.exec(strSelect);
    query.next();
    TeacherName = query.value(0).toString();
    ui->label_Welcome->setText(tr("Welcome enter %1 Teacher").arg(TeacherName));
    if(!m_Admin){
        QString sqlSelect1 = QString("select Permissions from TeacherInfor where TeacherID = '%1';").arg(m_strUser);
        if(!query.exec(sqlSelect1))
            return;
        while(query.next()){
            qDebug()<<"query.value(0).toString()="<<query.value(0).toString();
            if(query.value(0).toString() == tr("辅导员")){
               ui->comboBox_TeacherPower->addItem(tr("Manager's Student"));
            }
        }

        m_strSqlSelectMystudentEasy = m_strSqlSelectMystudentEasy.append(" where CourseRecord.CourseID in (select CourseID from Teacher_Course where TeacherID = '%1')").arg(m_strUser);
        m_strSqlSelectMystudentAll = m_strSqlSelectMystudentAll.append(" where CourseRecord.CourseID in (select CourseID from Teacher_Course where TeacherID = '%1')").arg(m_strUser);
        m_strSqlSelectManagerstudentAll = m_strSqlSelectManagerstudentAll.append(" where ClassInfor.ClassID = (select ClassID from ClassInfor where TeacherID = '%1')").arg(m_strUser);
        m_strSqlSelectManagerstudentEasy = m_strSqlSelectManagerstudentEasy.append(" where ClassInfor.ClassID = (select ClassID from ClassInfor where TeacherID = '%1')").arg(m_strUser);
    }
    ShowSelectInfor(m_strSqlSelectMystudentEasy);
}

CTeacher::~CTeacher()
{
    delete ui;
    delete m_pChangePwDlg;
}

void CTeacher::Init()
{
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
    QRegExp rx("[0-9]{12}");
    ui->lineEdit_Select->setValidator(new QRegExpValidator(rx, this));


    m_strSqlSelectMystudentEasy = QString("select CourseRecord.StudentID,StudentInfor.StudentName,ClassInfor.ClassName,CourseInfor.CourseName,CourseInfor.CourseID,CourseInfor.CourseCredit,CourseRecord.Achievement"
                                 " from CourseRecord"
                                 " left join StudentInfor,CourseInfor"
                                 " on CourseRecord.StudentID = StudentInfor.StudentID and CourseRecord.CourseID = CourseInfor.CourseID"
                                 " left join ClassInfor"
                                 " on StudentInfor.ClassID = ClassInfor.ClassID");

    m_strSqlSelectMystudentAll = QString("select CourseRecord.StudentID,StudentInfor.StudentName,StudentInfor.Sex,StudentInfor.Age,ClassInfor.Belong,ClassInfor.ClassName,CourseInfor.CourseName,CourseInfor.Scheduling,CourseInfor.CourseCredit,CourseInfor.CourseType,CourseRecord.Achievement,StudentInfor.StartTime,StudentInfor.HomeAdr"
                                         " from CourseRecord"
                                         " left join StudentInfor,CourseInfor"
                                         " on CourseRecord.StudentID = StudentInfor.StudentID and CourseRecord.CourseID = CourseInfor.CourseID"
                                         " left join ClassInfor"
                                         " on StudentInfor.ClassID = ClassInfor.ClassID");
    m_strSqlSelectManagerstudentAll = QString("select CourseRecord.StudentID,StudentInfor.StudentName,StudentInfor.Sex,StudentInfor.Age,ClassInfor.Belong,ClassInfor.ClassName,CourseInfor.CourseName,CourseInfor.Scheduling,CourseInfor.CourseCredit,CourseInfor.CourseType,CourseRecord.Achievement,StudentInfor.StartTime,StudentInfor.HomeAdr"
                                         " from CourseRecord"
                                         " left join StudentInfor,CourseInfor"
                                         " on CourseRecord.StudentID = StudentInfor.StudentID and CourseRecord.CourseID = CourseInfor.CourseID"
                                         " left join ClassInfor"
                                         " on StudentInfor.ClassID = ClassInfor.ClassID");
    m_strSqlSelectManagerstudentEasy = QString("select CourseRecord.StudentID,StudentInfor.StudentName,ClassInfor.ClassName,CourseInfor.CourseName,CourseInfor.CourseID,CourseInfor.CourseCredit,CourseRecord.Achievement"
                                " from CourseRecord"
                                " left join StudentInfor,CourseInfor"
                                " on CourseRecord.StudentID = StudentInfor.StudentID and CourseRecord.CourseID = CourseInfor.CourseID"
                                " left join ClassInfor"
                                " on StudentInfor.ClassID = ClassInfor.ClassID");

    QTimer::singleShot(0,this,&CTeacher::ON_SLOT_InitFinished);

}

void CTeacher::ShowSelectInfor(QString &str,SHOWTYPE type,IDSAVE issave)
{
    if(!m_pMode)
        m_pMode  = new QSqlQueryModel(this);
//    m_pMode->sort(6,Qt::AscendingOrder);
    m_pMode->setQuery(str) ;
    if(issave == IDSAVE::SAVE)
        m_strSqlSelectLast = str;

    if(type == SHOWTYPE::EASY){
        m_pMode->setHeaderData(0,Qt::Horizontal,QObject::tr("StudentlD"));
        m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("StudentName"));
        m_pMode->setHeaderData(2,Qt::Horizontal,QObject::tr("ClassName"));
        m_pMode->setHeaderData(3,Qt::Horizontal,QObject::tr("CourseName"));
        m_pMode->setHeaderData(4,Qt::Horizontal,QObject::tr("CourselD"));
        m_pMode->setHeaderData(5,Qt::Horizontal,QObject::tr("CourseCredit"));
        m_pMode->setHeaderData(6,Qt::Horizontal,QObject::tr("Achievement  "));
    }else{
        m_pMode->setHeaderData(0,Qt::Horizontal,QObject::tr("StudentlD"));
        m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("StudentName"));
        m_pMode->setHeaderData(2,Qt::Horizontal,QObject::tr("Sex"));
        m_pMode->setHeaderData(3,Qt::Horizontal,QObject::tr("Age"));
        m_pMode->setHeaderData(4,Qt::Horizontal,QObject::tr("Belong"));
        m_pMode->setHeaderData(5,Qt::Horizontal,QObject::tr("ClassName"));
        m_pMode->setHeaderData(6,Qt::Horizontal,QObject::tr("CourseName"));
        m_pMode->setHeaderData(7,Qt::Horizontal,QObject::tr("Scheduling"));
        m_pMode->setHeaderData(8,Qt::Horizontal,QObject::tr("CourseCredit"));
        m_pMode->setHeaderData(9,Qt::Horizontal,QObject::tr("CourseType"));
        m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("Achievement     "));
        m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("StartTime "));
        m_pMode->setHeaderData(1,Qt::Horizontal,QObject::tr("HomeAdr "));
    }
    //m_pMode->sort(6,Qt::AscendingOrder);
    ui->tableView->setModel(m_pMode);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void CTeacher::on_comboBox_TeacherPower_currentIndexChanged(int index)
{
    if(index == 0){
        if(ui->checkBox->isChecked()){
            ShowSelectInfor(m_strSqlSelectMystudentAll,SHOWTYPE::ALL);
            return;
        }
        ShowSelectInfor(m_strSqlSelectMystudentEasy);
        return ;
    }else if(index == 1){
        if(ui->checkBox->isChecked()){

            ShowSelectInfor(m_strSqlSelectManagerstudentAll,SHOWTYPE::ALL);
            return ;
        }

        ShowSelectInfor(m_strSqlSelectManagerstudentEasy);
        return ;
    }

}



void CTeacher::on_checkBox_stateChanged(int arg1)
{
    qDebug()<<"arg="<<arg1;
    if(arg1 == 0){
        if(ui->comboBox_TeacherPower->currentIndex() == 0){
            ShowSelectInfor(m_strSqlSelectMystudentEasy);
            return ;
        }else if(ui->comboBox_TeacherPower->currentIndex() == 1){
            ShowSelectInfor(m_strSqlSelectManagerstudentEasy);
            return ;
        }

    }else if(arg1 == 2){
        if(ui->comboBox_TeacherPower->currentIndex() == 0){
            ShowSelectInfor(m_strSqlSelectMystudentAll,SHOWTYPE::ALL);
            return ;
        }else if(ui->comboBox_TeacherPower->currentIndex() == 1){
            ShowSelectInfor(m_strSqlSelectManagerstudentAll,SHOWTYPE::ALL);
            return ;
        }
    }
}


void CTeacher::on_pushButton_Select_clicked()
{
if(ui->comboBox_Select->currentIndex() == 0&&ui->comboBox_TeacherPower->currentIndex() == 0){
    QString str = m_strSqlSelectMystudentEasy;
    str.append(QString(" and CourseRecord.StudentID = '%1'").arg(ui->lineEdit_Select->text()));
    ShowSelectInfor(str);
    return;
}else if(ui->comboBox_Select->currentIndex() == 0&&ui->comboBox_TeacherPower->currentIndex() == 1){
    QString str = m_strSqlSelectManagerstudentEasy;
    str.append(QString(" and CourseRecord.StudentID = '%1'").arg(ui->lineEdit_Select->text()));
    ShowSelectInfor(str);
    return;
}else if(ui->comboBox_Select->currentIndex() == 1&&ui->comboBox_TeacherPower->currentIndex() == 0){
    QString str = m_strSqlSelectMystudentEasy;
    str.append(QString(" and CourseInfor.CourseName = '%1'").arg(ui->lineEdit_Select->text()));
    ShowSelectInfor(str);
    return;
}else if(ui->comboBox_Select->currentIndex() == 1&&ui->comboBox_TeacherPower->currentIndex() == 1){
    QString str = m_strSqlSelectManagerstudentEasy;
    str.append(QString(" and CourseInfor.CourseName = '%1'").arg(ui->lineEdit_Select->text()));
    ShowSelectInfor(str);
    return;
}

}


void CTeacher::on_comboBox_Select_currentIndexChanged(int index)
{
    if(index == 0){
        QRegExp rx("[0-9]{12}");
        ui->lineEdit_Select->clear();
        ui->lineEdit_Select->setValidator(new QRegExpValidator(rx, this));
        return;
    }else{
        QRegExp rx("^[\\一-\\龥]{0,}$");
        ui->lineEdit_Select->clear();
        ui->lineEdit_Select->setValidator(new QRegExpValidator(rx, this));
        return;
    }
}



void CTeacher::on_pushButton_StartSort_clicked()
{
    if(!ui->radioButton_Asde->isChecked()&&!ui->radioButton_Desc->isChecked()){
        QMessageBox::warning(this,tr("error"),tr("please choose the type for sort"));
        return;
    }
    if(ui->radioButton_Asde->isChecked()&&ui->comboBox_TeacherPower->currentIndex() == 0 && ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectMystudentAll;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement"));
        ShowSelectInfor(str,SHOWTYPE::ALL,IDSAVE::NOTSAVE);
        return;
    }else if(ui->radioButton_Asde->isChecked() && ui->comboBox_TeacherPower->currentIndex() == 1 && ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectManagerstudentAll;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement"));
        ShowSelectInfor(str,SHOWTYPE::ALL,IDSAVE::NOTSAVE);
        return;
    }else if(ui->radioButton_Desc->isChecked()&&ui->comboBox_TeacherPower->currentIndex() == 0 && !ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectMystudentEasy;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement DESC"));
        ShowSelectInfor(str,SHOWTYPE::EASY,IDSAVE::NOTSAVE);
        return;
    }else if(ui->radioButton_Desc->isChecked()&&ui->comboBox_TeacherPower->currentIndex() == 0 && ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectMystudentAll;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement DESC"));
        ShowSelectInfor(str,SHOWTYPE::ALL,IDSAVE::NOTSAVE);
        return;
    }else if(ui->radioButton_Asde->isChecked() && ui->comboBox_TeacherPower->currentIndex() == 0 && !ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectMystudentEasy;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement"));
        ShowSelectInfor(str,SHOWTYPE::EASY,IDSAVE::NOTSAVE);
        return;
    }else if(ui->radioButton_Desc->isChecked() && ui->comboBox_TeacherPower->currentIndex() == 1 && ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectManagerstudentAll;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement DESC"));
        ShowSelectInfor(str,SHOWTYPE::ALL,IDSAVE::NOTSAVE);
        return;
    }else if(ui->radioButton_Asde->isChecked() && ui->comboBox_TeacherPower->currentIndex() == 1 && !ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectManagerstudentEasy;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement"));
        ShowSelectInfor(str,SHOWTYPE::EASY,IDSAVE::NOTSAVE);
        return;
    }else if(ui->radioButton_Desc->isChecked() && ui->comboBox_TeacherPower->currentIndex() == 1 && !ui->checkBox->isChecked()){
        //QString str = m_strSqlSelectManagerstudentEasy;
        QString str = m_strSqlSelectLast;
        str.append(QString(" ORDER BY CourseRecord.Achievement DESC"));
        ShowSelectInfor(str,SHOWTYPE::EASY,IDSAVE::NOTSAVE);
        return;
    }

//    ui->tableView->sortByColumn(6,Qt::AscendingOrder);
//    ui->tableView->update();
}


void CTeacher::on_pushButton_ModiftedAchi_clicked()
{
    if(m_pDlg){
        m_pDlg->show();
        return;
    }

    m_pDlg = new CModifyedAchiDialog(this);
    connect(this,&CTeacher::SendDatabase,m_pDlg,&CModifyedAchiDialog::ReciveDatabase);
    connect(m_pDlg,&CModifyedAchiDialog::sendUpdate,this,&CTeacher::ON_SLOT_UpdateTable);

    emit SendDatabase(m_Db,m_strUser,m_strSqlSelectManagerstudentEasy);

    m_pDlg->show();
}

void CTeacher::ON_SLOT_UpdateTable()
{
    int index = ui->comboBox_TeacherPower->currentIndex();
    if(index == 0){
        if(ui->checkBox->isChecked()){
            ShowSelectInfor(m_strSqlSelectMystudentAll,SHOWTYPE::ALL);
            return;
        }
        ShowSelectInfor(m_strSqlSelectMystudentEasy);
        return ;
    }else if(index == 1){
        if(ui->checkBox->isChecked()){

            ShowSelectInfor(m_strSqlSelectManagerstudentAll,SHOWTYPE::ALL);
            return ;
        }

        ShowSelectInfor(m_strSqlSelectManagerstudentEasy);
        return ;
    }

}


void CTeacher::on_pushButton_Disqualification_clicked()
{
    int index = ui->comboBox_TeacherPower->currentIndex();
    QString strSort;
    if(m_Admin){
        strSort = QString(" where CourseRecord.Achievement < '60'");
    }else{
        strSort = QString(" and CourseRecord.Achievement < '60'");
    }
    if(index == 0){
        if(ui->checkBox->isChecked()){
            QString str = m_strSqlSelectMystudentAll;
            str.append(strSort);
            ShowSelectInfor(str,SHOWTYPE::ALL);
            return;
        }
        QString str = m_strSqlSelectMystudentEasy;
        str.append(strSort);
        ShowSelectInfor(str);
        return;
    }else if(index == 1){
        if(ui->checkBox->isChecked()){
            QString str = m_strSqlSelectManagerstudentAll;
            str.append(strSort);
            ShowSelectInfor(str,SHOWTYPE::ALL);
            return;
        }
        QString str = m_strSqlSelectManagerstudentEasy;
        str.append(strSort);
        ShowSelectInfor(str);
        return;
    }
}


void CTeacher::on_pushButton_ChangePassword_clicked()
{
    if(m_pChangePwDlg){
        m_pChangePwDlg->show();
        return;
    }
    m_pChangePwDlg = new CDialog_ChangePassword(this);
    connect(this,&CTeacher::SendUser,m_pChangePwDlg,&CDialog_ChangePassword::ReciveUser);
    emit SendUser(m_strUser,1);
    m_pChangePwDlg->show();
}

