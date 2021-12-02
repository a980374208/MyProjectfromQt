#ifndef COURSEMANGER_H
#define COURSEMANGER_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>
#include "dialog_addcourse.h"

namespace Ui {
class CCourseManger;
}

class CCourseManger : public QMainWindow
{
    Q_OBJECT

public:
    explicit CCourseManger(QWidget *parent = nullptr);
    ~CCourseManger();
private slots:

    void on_pushButton_AddCourse_clicked();

    void on_pushButton_DeleteCourse_clicked();

private:
    void ShowCourseInfor();

    void GetSelectItemText(QString &ID,int index);

private:
    Ui::CCourseManger *ui;
    QSqlQuery                       m_query;
    QString                         m_strSelectCourseInfor;
    QVector<QMap<int,QString>>      m_vectorCourseInfor;
    CDialog_AddCourse*              m_pDialogAddCourse;
};

#endif // COURSEMANGER_H
