#ifndef DIALOG_REGISTER_H
#define DIALOG_REGISTER_H

#include <QDialog>

namespace Ui {
class CDialog_Register;
}

class CDialog_Register : public QDialog
{
    Q_OBJECT

public:
    explicit CDialog_Register(QWidget *parent = nullptr);
    ~CDialog_Register();

private slots:
    void on_pushButton_OK_clicked();

private:
    Ui::CDialog_Register *ui;
};

#endif // DIALOG_REGISTER_H
