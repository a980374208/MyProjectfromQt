#ifndef DIALOG_ADDCOURSE_H
#define DIALOG_ADDCOURSE_H

#include <QDialog>

namespace Ui {
class CDialog_AddCourse;
}

class CDialog_AddCourse : public QDialog
{
    Q_OBJECT

signals:
    void UpdateTable();

public:
    explicit CDialog_AddCourse(QWidget *parent = nullptr);
    ~CDialog_AddCourse();

private slots:
    void on_pushButton_OK_clicked();

private:
    Ui::CDialog_AddCourse *ui;
};

#endif // DIALOG_ADDCOURSE_H
