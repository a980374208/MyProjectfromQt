#ifndef MODIFYEDACHIDIALOG_H
#define MODIFYEDACHIDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace Ui {
class CModifyedAchiDialog;
}

class CModifyedAchiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CModifyedAchiDialog(QWidget *parent = nullptr);
    ~CModifyedAchiDialog();
signals:
    void sendUpdate();

private slots:

    void ON_SLOT_InitFinished();
    void on_pushButton_ok_clicked();
public slots:
     void ReciveDatabase(QSqlDatabase &db,QString user,QString sqlSel);
private:
     void reject()override;

private:
    Ui::CModifyedAchiDialog *ui;
    QSqlDatabase*      m_pDb;
    QString            m_strUser;
    QString            m_strSqlSelectMystudentEasy;
    QString            m_strSqlSelectManagerstudentEasy;
};

#endif // MODIFYEDACHIDIALOG_H
