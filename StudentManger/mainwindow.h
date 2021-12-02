#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <windows.h>
#include <windowsx.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include "student.h"
#include "dialog_register.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void SendDatabase(QSqlDatabase db,QString user,QString Password);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private slots:

    void on_radioButton_Student_toggled(bool checked);

    void on_radioButton_Teacher_toggled(bool checked);

    void on_radioButton_Admin_toggled(bool checked);

    void on_pushButton_Close_clicked();

    void on_pushButton_Login_clicked();

    void on_pushButton_Register_clicked();

private:
    void Init();                               //初始化
    void SetInterfaceBg(QString &str);         //设置界面ui

private:
    Ui::MainWindow *ui;

    int                boundaryWidth;
    QPoint             m_clickPos;
    QSqlDatabase       m_Db;
    QString            m_strUser;
    QString            m_strPassword;
    CDialog_Register*  m_pDiaRegister;



};
#endif // MAINWINDOW_H
