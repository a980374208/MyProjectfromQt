#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>


void MainWindow::CreateChart()
{
    QChart *chart = new QChart;
    chart->setTitle("Chart");
    ui->MyChartView->setChart(chart);
    QLineSeries *seriesSin = new QLineSeries;
    QLineSeries *seriesCos = new QLineSeries;
    seriesSin->setName("Sin曲线");
    seriesCos->setName("Cos曲线");
    chart->addSeries(seriesSin);
    chart->addSeries(seriesCos);
    chart->createDefaultAxes();
    chart->axisX()->setRange(-1,11);
    chart->axisY()->setRange(-1.1,1.1);
    foreach (auto marker, ui->MyChartView->chart()->legend()->markers()) {
        connect(marker,SIGNAL(clicked()),SLOT(ON_LegendClick()));
    }

}

void MainWindow::PrepareData()
{
    QLineSeries *seriesSin = (QLineSeries *)ui->MyChartView->chart()->series().at(0);
    QLineSeries *seriesCos = (QLineSeries *)ui->MyChartView->chart()->series().at(1);
    qsrand(QTime::currentTime().second());
    qreal x=0,y,y1;
    for(int i=0;i<100;++i){
        y=(qrand()%5-5)/10+qSin(x);
        y1=(qrand()%5-5)/10+qCos(x);
        x+=0.1;
        seriesCos->append(x,y1);
        seriesSin->append(x,y);
    }



}

void MainWindow::ON_mouseMoveEvent(QPoint *point)
{
    QPointF pointA = ui->MyChartView->chart()->mapToValue(*point);
    AxisPosLabel->setText(QString::asprintf("Axis内位置:X:%.1f,Y:%.1f",pointA.x(),pointA.y()));
//    QPointF pt=ui->MyChartView->chart()->mapToValue(*point); //转换为图表的数值

//    AxisPosLabel->setText(QString::asprintf("X=%.1f,Y=%.2f",pt.x(),pt.y())); //状态栏显示

}

void MainWindow::ON_LegendClick()
{
   auto marker = (QLegendMarker*)sender();
   marker->series()->setVisible(!marker->series()->isVisible());
   marker->setVisible(true);

   int alpha = 255;
   if(!marker->series()->isVisible())
       alpha = 122;

   QBrush brush = marker->labelBrush();
   QColor color = brush.color();
   color.setAlpha(alpha);
   brush.setColor(color);
   marker->setLabelBrush(brush);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pChart = new QMyChartView;
    AxisPosLabel = new QLabel;
    AxisPosLabel->setMinimumWidth(150);
    statusBar()->addWidget(AxisPosLabel);

    ui->MyChartView->setWindowTitle("chart");
    setCentralWidget(ui->MyChartView);
    CreateChart();
    PrepareData();
    connect(ui->MyChartView,SIGNAL(SendPoint(QPoint*))
            ,this,SLOT(ON_mouseMoveEvent(QPoint*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actZoomIn_triggered()
{
    ui->MyChartView->chart()->zoom(0.8);
}


void MainWindow::on_actZoomOut_triggered()
{
     ui->MyChartView->chart()->zoom(1.2);
}


void MainWindow::on_actZoomReset_triggered()
{
    ui->MyChartView->chart()->zoomReset();
}

