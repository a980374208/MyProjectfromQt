#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager   m_NetworkManger;
    QNetworkReply*          m_pReply;
    QFile*                  m_pDownloadFile;

private slots:
    void on_finished();
    void on_readyRead();
    void on_downloadProgress(qint64 bytesRead,qint64 totalBttes);
    void on_btnDefaultPath_clicked();
    void on_btnDownload_clicked();
};
#endif // MAINWINDOW_H
