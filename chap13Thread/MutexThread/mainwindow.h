#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_threadANewValue(int seq,int diceValue);
    void on_threadAStarted();
    void on_threadAFinished();

    void On_timerOut();

    void on_btnStartThread_clicked();

    void on_btnDiceBegin_clicked();

    void on_btnDiceEnd_clicked();

    void on_btnStopThread_clicked();

    void on_btnClear_clicked();

protected:
    void closeEvent(QCloseEvent* event)Q_DECL_OVERRIDE;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyThread thread;
    QTimer timer;
};
#endif // MAINWINDOW_H
