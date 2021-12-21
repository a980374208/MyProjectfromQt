#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_SendMsg_clicked();

    void on_pushButton_setConnect_clicked();

    void on_pushButton_setDisConnect_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket* m_tcp;
    QLabel* m_status;
};
#endif // MAINWINDOW_H
