#ifndef DIALOG_APPOINTTABLE_H
#define DIALOG_APPOINTTABLE_H

#include <QDialog>
#include <QSqlQuery>
#include <QMap>
#include <QVector>

namespace Ui {
class CDialog_AppointTable;
}

class CDialog_AppointTable : public QDialog
{
    Q_OBJECT

signals:
    void UpdateView();


public slots:
    void ON_SLOT_ReciveNoCounClass(QString &a);

    void ON_SLOT_ReciveNoTeaCourse(QString &a);

    void ON_ShowTable();

    void ON_SLOT_ReciverID(QString a);




public:
    explicit CDialog_AppointTable(QWidget *parent = nullptr);
    ~CDialog_AppointTable();

private slots:
    void on_pushButton_OK_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_Cancel_clicked();

private:
    Ui::CDialog_AppointTable *ui;
    QString                        m_strSqlNoCounselorClass;
    QString                        m_strSqlNoTeacherCourse;
    QSqlQuery                      query;

    QVector<QMap<int,QString>>       m_listNoTeacherClass;
    QVector<QMap<int,QString>>       m_listNoCounselorClass;
    QString                        m_strTeacherID;
    int                            role;
    int                            m_CurrentSelectedRow;

};

#endif // DIALOG_APPOINTTABLE_H
