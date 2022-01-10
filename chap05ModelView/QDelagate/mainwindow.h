#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include "qintspindelegate.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void ON_currentChanged(const QModelIndex& current, const QModelIndex& previous);

    void on_actOpen_triggered();

    void on_actSave_triggered();

    void on_actModelData_triggered();

    void on_actAppend_triggered();

    void on_actInsert_triggered();

    void on_actDelete_triggered();

    void on_actAlignLeft_triggered();

    void on_actAlignCenter_triggered();

    void on_actAlignRight_triggered();


    void on_actFontBold_triggered(bool checked);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void iniModelFromStringList(QStringList& fileContent);
    void SetActAlign(Qt::Alignment actAlign);

private:
    Ui::MainWindow *ui;
    QLabel * m_pLabCurFiel;
    QLabel * m_pLabCellPos;
    QLabel * m_pLabCellText;

    QStandardItemModel *m_pTheModel;
    QItemSelectionModel *m_pTheSelection;

    QIntSpinDelegate m_IntSpinDeledate;
};
#endif // MAINWINDOW_H
