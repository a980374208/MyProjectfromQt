#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QLabel>
#include <QHostInfo>

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
    void on_SockerStateChange(QAbstractSocket::SocketState socketState);
    void on_SocketReadrRead();

    void on_actStart_triggered();

    void on_actStop_triggered();


    void on_btnSend_clicked();

    void on_actClear_triggered();

    void on_btnBroadcast_clicked();

private:
    Ui::MainWindow *ui;
    QLabel     *m_pLabSocketState;
    QUdpSocket *m_pUdpSocket;

};
#endif // MAINWINDOW_H
