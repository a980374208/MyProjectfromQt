#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "cmycomboxdelegate.h"
#include <QDataWidgetMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void ON_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void ON_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);


    void on_actOpenDB_triggered();

    void on_actRecAppend_triggered();

    void on_actRecInsert_triggered();

    void on_actRecDelete_triggered();

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

    void on_actPhotoClear_triggered();

    void on_actPhoto_triggered();

    void on_actScan_triggered();

    void on_comboFields_currentIndexChanged(int index);

    void on_radioBtnAscend_clicked();

    void on_radioBtnDescend_clicked();

    void on_radioBtnMan_clicked();

    void on_radioBtnWoman_clicked();

    void on_radioBtnBoth_clicked();

private:
    void  openTable();


    void  GetFiledNames();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlTableModel* m_pSqlTablemodel;
    QItemSelectionModel* m_pSelectModel;
    CMyComboxDelegate  m_DelegateSex;
    CMyComboxDelegate  m_DelegateDepart;
    QDataWidgetMapper* m_pDataMapper;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
