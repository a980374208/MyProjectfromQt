#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qmythread.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event)Q_DECL_OVERRIDE;

private slots:
    void on_btnStartThread_clicked();

    void ON_ProducerStarted();
    void ON_ProducerFinished();

    void ON_ConsumerStarted();
    void ON_ConsumerFinished();
    void ON_ConsumerValueChanged(int *data,int conunter,int seq);

    void on_btnStopThread_clicked();


    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    QMyThread     m_ThreadProducer;
    QMyThreadShow m_ThreadConsumer;
};
#endif // MAINWINDOW_H
