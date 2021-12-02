#ifndef DIALOG_ADDTEACHER_H
#define DIALOG_ADDTEACHER_H

#include <QDialog>

namespace Ui {
class CDialog_AddTeacher;
}

class CDialog_AddTeacher : public QDialog
{
    Q_OBJECT

signals:
    void SendUpdate();

public:
    explicit CDialog_AddTeacher(QWidget *parent = nullptr);
    ~CDialog_AddTeacher();

private slots:
    void on_pushButton_OK_clicked();

private:
    void reject()override;
private:
    Ui::CDialog_AddTeacher *ui;
};

#endif // DIALOG_ADDTEACHER_H
