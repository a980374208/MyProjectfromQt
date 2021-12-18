#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmychartview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void CreateChart();
    void PrepareData();

private slots:
    void ON_mouseMoveEvent(QPoint *point);
    void ON_LegendClick();


    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomReset_triggered();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMyChartView*  m_pChart;
    QLabel * AxisPosLabel;
};
#endif // MAINWINDOW_H
