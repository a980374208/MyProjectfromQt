#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QHostInfo>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void onSocketStateChange(QAbstractSocket::SocketState socketState);

    void onSocketReadyRead();



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_actClear_triggered();

    void on_btnMulticast_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket*    m_pUdpSocket;
    QHostAddress  m_GroupAddress;
    QLabel*        m_pLabSocketState;
};
#endif // MAINWINDOW_H
