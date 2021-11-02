#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_pushButton_SelectFile_clicked();

    void on_pushButton_SetConnect_clicked();
    void on_pushButton_SendFile_clicked();

signals:
    void StartConnect(unsigned short port, QString ip);
    void StartSend(QString path);

private:
    Ui::MainWindow *ui;
    QTcpSocket*    m_tcp;
    QThread*       m_t;
};
#endif // MAINWINDOW_H
