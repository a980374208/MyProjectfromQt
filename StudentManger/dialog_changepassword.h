#ifndef DIALOG_CHANGEPASSWORD_H
#define DIALOG_CHANGEPASSWORD_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class CDialog_ChangePassword;
}

class CDialog_ChangePassword : public QDialog
{
    Q_OBJECT


public:
    void ReciveUser(QString user,int role);
private slots:
    void ON_InitFinshied();
    void on_pushButton_ConfirmChange_clicked();
    void reject() override;

public:
    explicit CDialog_ChangePassword(QWidget *parent = nullptr);
    ~CDialog_ChangePassword();

private:
    Ui::CDialog_ChangePassword *ui;

    QString m_srUser;
    int m_Father;
};

#endif // DIALOG_CHANGEPASSWORD_H
