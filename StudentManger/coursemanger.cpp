#include "coursemanger.h"
#include "ui_coursemanger.h"
#include <QMessageBox>

CCourseManger::CCourseManger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CCourseManger)
{
    ui->setupUi(this);
    m_pDialogAddCourse = nullptr;
    m_strSelectCourseInfor = QString("select * from CourseInfor");

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ShowCourseInfor();

}

CCourseManger::~CCourseManger()
{
    delete ui;
}

void CCourseManger::ShowCourseInfor()
{
    m_vectorCourseInfor.clear();
    QMap<int,QString>                 tempmap;

    m_query.exec(m_strSelectCourseInfor);
    while(m_query.next()){
        tempmap[0] = m_query.value(0).toString();
        tempmap[1] = m_query.value(1).toString();
        tempmap[2] = m_query.value(2).toString();
        tempmap[3] = m_query.value(3).toString();
        tempmap[4] = m_query.value(4).toString();
        m_vectorCourseInfor.push_back(tempmap);
    }

    QMap<int,QString>                 tempmap1;
    int size = m_vectorCourseInfor.size();
    ui->tableWidget->setRowCount(size);
    ui->tableWidget->setColumnCount(5);
    QStringList header;
    header<<tr("CourseID")<<tr("CourseName")<<tr("Scheduling")<<tr("CourseCredit")<<tr("CourseType");
    ui->tableWidget->setHorizontalHeaderLabels(header);


    for(int index = 0;index<size;++index){
        tempmap1 = m_vectorCourseInfor.at(index);
        qDebug()<<m_vectorCourseInfor.at(index);
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(tempmap1[0]));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(tempmap1[1]));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(tempmap1[2]));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(tempmap1[3]));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(tempmap1[4]));
    }
}

void CCourseManger::GetSelectItemText(QString &ID,int index)
{

    QVariant Id = ui->tableWidget->model()->data(ui->tableWidget->model()->index(ui->tableWidget->currentIndex().row(),index));
    //QVariant Permissions = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5));
    ID = Id.toString();
    //Preimissions = Permissions.toString();

}




void CCourseManger::on_pushButton_AddCourse_clicked()
{
    if(m_pDialogAddCourse){
        m_pDialogAddCourse->show();
        return;
    }
    m_pDialogAddCourse = new CDialog_AddCourse(this);
    connect(m_pDialogAddCourse,&CDialog_AddCourse::UpdateTable,this,[=](){
       ShowCourseInfor();
    });
    m_pDialogAddCourse->show();
}


void CCourseManger::on_pushButton_DeleteCourse_clicked()
{
    QString CourseID;

    GetSelectItemText(CourseID,0);
    qDebug()<<"CourSEID="<<CourseID;
    QString strSql = QString("select * from CourseRecord where CourseID = '%1'").arg(CourseID);
    m_query.exec(strSql);
    if(m_query.next()){
        QMessageBox::warning(this,tr("error"),tr("还有学生选修此课程您不能删除。"));
        return;
    }
    QString strSql1 = QString("select TeacherID from Teacher_Course where CourseID = '%1'").arg(CourseID);
    m_query.exec(strSql1);
    if(m_query.next()){
        if(!m_query.value(0).isNull()){
            QMessageBox::warning(this,tr("error"),tr("还有教师教授此课程请取消教师授课后删除课程。"));
            return;
        }
    }
    QString strSql2 = QString("delete from CourseInfor where CourseID = '%1'").arg(CourseID);
    QString strSql3 = QString("delete from Teacher_Course where CourseID = '%1'").arg(CourseID);
    if(m_query.exec(strSql2)){
        if(m_query.exec(strSql3)){
            QMessageBox::information(this,tr("success"),tr("删除课程此课程成功。"));
            ShowCourseInfor();
            return;
        }
    }


}

