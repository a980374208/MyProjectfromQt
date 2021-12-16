#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineSeries>
#include <QtMath>
#include <QValueAxis>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QChartView *chartView = new QChartView(this);
    QChart *chart = new QChart;
    chartView->setChart(chart);
    chart->setTitle("简单函数曲线");


    setCentralWidget(chartView);
        QLineSeries* series0 = new QLineSeries;
        QLineSeries* series1 = new QLineSeries();
        series1->setName("Cos曲线");
        series0->setName("Sin曲线");
        chart->addSeries(series0);
        chart->addSeries(series1);
        qreal y0,y1,t=0,interval = 0.1;
        int cnt = 100;
        for(int i= 0 ;i<cnt;++i){
            y0 = qSin(t);
            y1 = qCos(t);
            series0->append(t,y0);
            series1->append(t,y1);
            t+=interval;
        }
        QValueAxis *axisX = new QValueAxis;
        QValueAxis *axisY = new QValueAxis;
        axisX->setRange(0,10);
        axisY->setRange(-1.1,1.1);

        chart->setAxisX(axisX,series0);
        chart->setAxisY(axisY,series1);
        chart->setAxisX(axisX,series1);
        chart->setAxisY(axisY,series0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

