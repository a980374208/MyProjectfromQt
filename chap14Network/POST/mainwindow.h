#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QNetworkRequest"


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
    void on_pushButton_clicked();
    void finishedSlot(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *nam;
};
#endif // MAINWINDOW_H
