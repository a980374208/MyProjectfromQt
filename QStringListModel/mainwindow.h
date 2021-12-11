#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

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
    void on_btnListAppend_clicked();

    void on_btnListInsert_clicked();

    void on_btnIniList_clicked();

    void on_btnListDelete_clicked();

    void on_btnListClear_clicked();

    void on_btnTextClear_clicked();

    void on_btnTextImport_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStringListModel* m_pTheModel;
};
#endif // MAINWINDOW_H
