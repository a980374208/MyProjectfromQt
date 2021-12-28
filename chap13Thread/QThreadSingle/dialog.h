#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

private slots:
    void on_threadANewValue(int seq,int diceValue);
    void on_threadAStarted();
    void on_threadAFinished();

    void on_btnStartThread_clicked();

    void on_btnDiceBegin_clicked();

    void on_btnDiceEnd_clicked();

    void on_btnStopThread_clicked();

    void on_btnClear_clicked();

protected:
    void closeEvent(QCloseEvent* event)Q_DECL_OVERRIDE;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

    MyThread thread;
};
#endif // DIALOG_H
