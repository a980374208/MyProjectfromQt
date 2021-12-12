#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>

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
    void on_actTabReset_triggered();

    void on_actOpen_triggered();

    void on_actSave_triggered();

    void on_actOpenBin_triggered();

    void on_actSaveBin_triggered();

private:
    void ResetTable(int rows);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_theModel;
    QItemSelectionModel *m_theSelect;
};
#endif // MAINWINDOW_H
