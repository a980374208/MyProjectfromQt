#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <cdialogpen.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CreateChart();
    PrepareData();
    UpdateFromChart();




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actZoomIn_triggered()
{
    ui->chartView->chart()->zoom(1.1);
}


void MainWindow::on_actZoomOut_triggered()
{
    ui->chartView->chart()->zoom(0.9);
}


void MainWindow::on_actZoomReset_triggered()
{
    ui->chartView->chart()->zoomReset();
}

void MainWindow::CreateChart()
{
    m_pChart = new QChart;
    m_pChart->setTitle("简单曲线");
    ui->chartView->setChart(m_pChart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    QLineSeries *series0 = new QLineSeries;
    QLineSeries *series1 = new QLineSeries;
    m_pCurSeries = series0;
    m_pCurAxis = axisX;
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    series0->setPen(pen);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series1->setPen(pen);

    m_pChart->addSeries(series0);
    m_pChart->addSeries(series1);

    axisX->setRange(-7,7);
    axisX->setLabelFormat("%.1f");
    axisX->setTickCount(15);
    axisX->setMinorTickCount(4);
    axisX->setTitleText("X轴");
    axisY->setRange(-1.5,1.5);
    axisY->setLabelFormat("%.1f");
    axisY->setTickCount(5);
    axisY->setMinorTickCount(4);
    axisY->setTitleText("Y轴");


    m_pChart->setAxisX(axisX,series0);
    m_pChart->setAxisX(axisX,series1);
    m_pChart->setAxisY(axisY,series0);
    m_pChart->setAxisY(axisY,series1);


}

void MainWindow::PrepareData()
{
    QLineSeries *series0 = (QLineSeries *)ui->chartView->chart()->series().at(0);
    QLineSeries *series1 = (QLineSeries *)ui->chartView->chart()->series().at(1);
    series0->clear();
    series1->clear();
    int cnt = 140;
    qsrand(QTime::currentTime().second());
    qreal rd;
    qreal x=-7,y1,y2,interval = 0.1;
    for(int i = 0;i<cnt;++i){
        rd = (qrand()%10)-5;
        y1 = qSin(x)+rd/50;
        series0->append(x,y1);
        y2 = qCos(x)+rd/50;
        series1->append(x,y2);
        x+= interval;
    }
}

void MainWindow::UpdateFromChart()
{
    QChart* chart = ui->chartView->chart();
    ui->editTitle->setText(chart->title());
    QMargins mg = chart->margins();
    ui->spinMarginLeft->setValue(mg.left());
    ui->spinMarginBottom->setValue(mg.bottom());
    ui->spinMarginRight->setValue(mg.right());
    ui->spinMarginTop->setValue(mg.top());

}


void MainWindow::on_actDraw_triggered()
{
    PrepareData();
}


void MainWindow::on_btnSetTitle_clicked()
{
    m_pChart->setTitle(ui->editTitle->text());
}

#include <QFontDialog>
void MainWindow::on_btnSetTitleFont_clicked()
{
    QFont font = ui->chartView->chart()->titleFont();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font);
    if(ok)
        ui->chartView->chart()->setTitleFont(font);

}


void MainWindow::on_radioButton_clicked()
{
    ui->chartView->chart()->legend()->setAlignment(Qt::AlignTop);

}


void MainWindow::on_radioButton_2_clicked()
{
     ui->chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
}


void MainWindow::on_radioButton_3_clicked()
{
     ui->chartView->chart()->legend()->setAlignment(Qt::AlignLeft);
}


void MainWindow::on_radioButton_4_clicked()
{
    ui->chartView->chart()->legend()->setAlignment(Qt::AlignRight);
}


void MainWindow::on_chkLegendVisible_clicked(bool checked)
{
    m_pChart->legend()->setVisible(checked);
}


void MainWindow::on_chkBoxLegendBackground_clicked(bool checked)
{
    m_pChart->legend()->setBackgroundVisible(checked);
}


void MainWindow::on_btnLegendFont_clicked()
{
    QFont font = m_pChart->legend()->font();
    bool ok;
    font = QFontDialog::getFont(&ok,font);
    if(ok)
        m_pChart->legend()->setFont(font);

}


void MainWindow::on_btnLegendlabelColor_clicked()
{
    QColor color = m_pChart->legend()->labelColor();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        m_pChart->legend()->setLabelColor(color);

}


void MainWindow::on_btnSetMargin_clicked()
{
    QMargins margin;
    margin.setBottom(ui->spinMarginBottom->value());
    margin.setTop(ui->spinMarginTop->value());
    margin.setLeft(ui->spinMarginLeft->value());
    margin.setRight(ui->spinMarginRight->value());
    m_pChart->setMargins(margin);
}





void MainWindow::on_cBoxAnimation_currentIndexChanged(int index)
{
    ui->chartView->chart()->setAnimationOptions((QChart::AnimationOption)index);
}


void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    m_pChart->setTheme(QChart::ChartTheme(index));
}


void MainWindow::on_radioSeries0_clicked()
{

    m_pCurSeries =(QLineSeries*) m_pChart->series().at(0);
    ui->editSeriesName->setText(m_pCurSeries->name());
    ui->chkSeriesVisible->setChecked(m_pCurSeries->isVisible());
    ui->chkPointVisible->setChecked(m_pCurSeries->pointsVisible());
    ui->sliderSeriesOpacity->setValue(m_pCurSeries->opacity()*10);
    ui->chkPointLabelVisible->setChecked(m_pCurSeries->pointLabelsVisible());

}


void MainWindow::on_radioSeries1_clicked()
{
    m_pCurSeries = (QLineSeries*)m_pChart->series().at(1);
    ui->editSeriesName->setText(m_pCurSeries->name());
    ui->chkSeriesVisible->setChecked(m_pCurSeries->isVisible());
    ui->chkPointVisible->setChecked(m_pCurSeries->pointsVisible());
    ui->sliderSeriesOpacity->setValue(m_pCurSeries->opacity()*10);
    ui->chkPointLabelVisible->setChecked(m_pCurSeries->pointLabelsVisible());

}


void MainWindow::on_chkSeriesVisible_clicked(bool checked)
{
    m_pCurSeries->setVisible(checked);
}


void MainWindow::on_chkPointVisible_clicked(bool checked)
{
    m_pCurSeries->setPointsVisible(checked);
}


void MainWindow::on_btnSeriesName_clicked()
{
    m_pCurSeries->setName(ui->editSeriesName->text());
}



void MainWindow::on_btnSeriesColor_clicked()
{
    QColor color = m_pCurSeries->color();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        m_pCurSeries->setColor(color);
}


void MainWindow::on_btnSeriesPen_clicked()
{
    QPen pen = m_pCurSeries->pen();
    bool ok= false;
    pen = CDialogPen::getPen(pen,ok);
    if(ok)
        m_pCurSeries->setPen(pen);

}


void MainWindow::on_sliderSeriesOpacity_valueChanged(int value)
{
    m_pCurSeries->setOpacity(value/10.0);
}


void MainWindow::on_radioSeriesLabFormat0_clicked()
{
    if(ui->radioSeriesLabFormat0->isChecked())
        m_pCurSeries->setPointLabelsFormat("@yPonit");
    else
        m_pCurSeries->setPointLabelsFormat("@xPonit,@yPoint");
}


void MainWindow::on_chkPointLabelVisible_clicked(bool checked)
{
    m_pCurSeries->setPointLabelsVisible(checked);
}


void MainWindow::on_btnSeriesLabColor_clicked()
{
    QColor color = m_pCurSeries->pointLabelsColor();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        m_pCurSeries->setPointLabelsColor(color);
}


void MainWindow::on_btnSeriesLabFont_clicked()
{
    QFont font = m_pCurSeries->pointLabelsFont();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font);
    if(ok)
        m_pCurSeries->setPointLabelsFont(font);
}


void MainWindow::on_radioSeriesLabFormat1_clicked()
{
    if(ui->radioSeriesLabFormat0->isChecked())
        m_pCurSeries->setPointLabelsFormat("@yPonit");
    else
        m_pCurSeries->setPointLabelsFormat("@xPonit,@yPoint");
}


void MainWindow::on_radioX_clicked()
{
    if(ui->radioX->isChecked())
        m_pCurAxis =(QValueAxis*) m_pChart->axisX();
    else
        m_pCurAxis = (QValueAxis*)m_pChart->axisY();
    ui->editAxisTitle->setText(m_pCurAxis->titleText());
    ui->chkBoxAxisTitle->setChecked(m_pCurAxis->isTitleVisible());
    ui->spinAxisMin->setValue(m_pCurAxis->min());
    ui->spinAxisMax->setValue(m_pCurAxis->max());
    ui->chkBoxVisible->setChecked(m_pCurAxis->isVisible());

    ui->editAxisLabelFormat->setText(m_pCurAxis->labelFormat());
    ui->chkBoxLabelsVisible->setChecked(m_pCurAxis->labelsVisible());

    ui->chkGridLineVisible->setChecked(m_pCurAxis->isGridLineVisible());
    ui->chkAxisLineVisible->setChecked(m_pCurAxis->isLineVisible());

    ui->spinTickCount->setValue(m_pCurAxis->tickCount());
    ui->chkAxisLineVisible->setChecked(m_pCurAxis->isLineVisible());

    ui->spinMinorTickCount->setValue(m_pCurAxis->minorTickCount());
    ui->chkMinorTickVisible->setChecked(m_pCurAxis->isMinorGridLineVisible());



}


void MainWindow::on_radioY_clicked()
{
    on_radioX_clicked();
}


void MainWindow::on_chkBoxVisible_clicked(bool checked)
{
    m_pCurAxis->setVisible(checked);
}


void MainWindow::on_btnSetAxisRange_clicked()
{
    m_pCurAxis->setRange(ui->spinAxisMin->value(),ui->spinAxisMax->value());
}


void MainWindow::on_btnAxisSetTitle_clicked()
{
    m_pCurAxis->setTitleText(ui->editAxisTitle->text());
}


void MainWindow::on_btnAxisSetTitleFont_clicked()
{
    QFont font = m_pCurAxis->titleFont();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font);
    if(ok)
        m_pCurAxis->setTitleFont(font);
}


void MainWindow::on_chkBoxAxisTitle_clicked(bool checked)
{
    m_pCurAxis->setTitleVisible(checked);
}


void MainWindow::on_pushButton_clicked()
{
    m_pCurAxis->setLabelFormat(ui->editAxisLabelFormat->text());
}


void MainWindow::on_btnAxisLabelColor_clicked()
{
    QColor color = m_pCurAxis->labelsColor();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        m_pCurAxis->setLabelsColor(color);
}


void MainWindow::on_btnAxisLabelFont_clicked()
{
    QFont font = m_pCurAxis->labelsFont();
    bool ok = false;
    font = QFontDialog::getFont(&ok,font);
    if(ok)
        m_pCurAxis->setLabelsFont(font);
}


void MainWindow::on_chkBoxLabelsVisible_clicked(bool checked)
{
    m_pCurAxis->setLabelsVisible(checked);
}


void MainWindow::on_chkGridLineVisible_clicked(bool checked)
{
    m_pCurAxis->setGridLineVisible(checked);
}


void MainWindow::on_btnGridLineColor_clicked()
{
    QColor color = m_pCurAxis->gridLineColor();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        m_pCurAxis->setGridLineColor(color);
}


void MainWindow::on_pushButton_10_clicked()
{
    QPen pen = m_pCurAxis->gridLinePen();
    bool ok =false;
    pen = CDialogPen::getPen(pen,ok);
    if(ok)
        m_pCurAxis->setGridLinePen(pen);
}


void MainWindow::on_spinTickCount_valueChanged(int arg1)
{
    m_pCurAxis->setTickCount(arg1);
}


void MainWindow::on_chkAxisLineVisible_clicked(bool checked)
{
    m_pCurAxis->setLineVisible(checked);
}


void MainWindow::on_btnAxisLinePen_clicked()
{
    QPen pen = m_pCurAxis->linePen();
    bool ok =false;
    pen = CDialogPen::getPen(pen,ok);
    if(ok)
        m_pCurAxis->setLinePen(pen);
}


void MainWindow::on_btnAxisLinePenColor_clicked()
{
    QColor color = m_pCurAxis->linePenColor();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        m_pCurAxis->setLinePenColor(color);
}


void MainWindow::on_spinMinorTickCount_valueChanged(int arg1)
{
    m_pCurAxis->setMinorTickCount(arg1);
}


void MainWindow::on_chkMinorTickVisible_clicked(bool checked)
{
    m_pCurAxis->setMinorGridLineVisible(checked);
}


void MainWindow::on_btnMinorColor_clicked()
{
    QColor color = m_pCurAxis->minorGridLineColor();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        m_pCurAxis->setMinorGridLineColor(color);
}


void MainWindow::on_btnMinorPen_clicked()
{
    QPen pen = m_pCurAxis->minorGridLinePen();
    bool ok =false;
    pen = CDialogPen::getPen(pen,ok);
    if(ok)
        m_pCurAxis->setMinorGridLinePen(pen);
}




