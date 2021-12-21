#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pTheModel = new QStandardItemModel(iniDataRowCount,fixedColumnCount,this);
    qsrand(QTime::currentTime().second());
    PrepareData();
    SurveyData();

    initBarChart();
    buildBarChart();

    initPieChart();
    buildPieChart();

    initStackedBarChart();
    buildStackedBarChart();

    initPrecentChart();
    buildPrecentChart();

    initScatterChart();
    buildScatterChart();
    ui->tableView->setModel(m_pTheModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PrepareData()
{
    QStringList headerList;
    headerList<<"姓名"<<"数学"<<"语文"<<"英语"<<"平均分";
    m_pTheModel->setHorizontalHeaderLabels(headerList);
    qreal avgAge;
    QStandardItem * aItem;

    QString studentName;
    for(int i = 0;i<m_pTheModel->rowCount();++i){
        avgAge = 0;
        studentName = QString::asprintf("学生%2d",i+1);
        aItem = new QStandardItem(studentName);
        aItem->setTextAlignment(Qt::AlignHCenter);
        m_pTheModel->setItem(i,colNoName,aItem);
        for(int j = colNoMath;j<=colNoEnglish;++j){
            int score = qrand()%50+50;
            aItem = new QStandardItem(QString::asprintf("%2d",score));
            aItem->setTextAlignment(Qt::AlignHCenter);
            m_pTheModel->setItem(i,j,aItem);
            avgAge += score;
        }
        avgAge /=3;
        aItem = new QStandardItem(QString::asprintf("%.2f",avgAge));
        aItem->setTextAlignment(Qt::AlignHCenter);
        aItem->setFlags(aItem->flags()&!Qt::ItemIsEditable);
        m_pTheModel->setItem(i,colNoAverage,aItem);
    }
}

void MainWindow::SurveyData()
{
    for(int i =colNoMath;i<=colNoAverage;++i){
        qreal minVal = 100,maxVal =0,val;
        qreal avgAge =0;
        int cnt50 = 0,cnt60 = 0,cnt70 = 0,cnt80 = 0,cnt90 = 0;
        for(int j=0;j<m_pTheModel->rowCount();++j){
            val = m_pTheModel->item(j,i)->text().toDouble(
                        );
            if(val>maxVal) maxVal = val;
            if(val<minVal) minVal = val;

            if(val<60) cnt50++;
            else if(val<70) cnt60++;
            else if(val<80) cnt70++;
            else if(val<90) cnt80++;
            else cnt90++;
            avgAge+=val;
        }
        QTreeWidgetItem* aItem = ui->treeWidget->topLevelItem(0);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(cnt50));

        aItem = ui->treeWidget->topLevelItem(1);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(cnt60));

        aItem = ui->treeWidget->topLevelItem(2);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(cnt70));

        aItem = ui->treeWidget->topLevelItem(3);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(cnt80));

        aItem = ui->treeWidget->topLevelItem(4);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(cnt90));

        aItem = ui->treeWidget->topLevelItem(5);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(avgAge/m_pTheModel->rowCount()));

        aItem = ui->treeWidget->topLevelItem(6);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(maxVal));

        aItem = ui->treeWidget->topLevelItem(7);
        aItem->setTextAlignment(i,Qt::AlignHCenter);
        aItem->setText(i,QString::number(minVal));

    }
}

void MainWindow::initBarChart()
{
    QChart *chart = new QChart;
    chart->setTitle("BarChart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewBar->setChart(chart);
    ui->chartViewBar->setRenderHint(QPainter::Antialiasing);

}

void MainWindow::buildBarChart()
{
    QChart *chart = ui->chartViewBar->chart();
    chart->removeAllSeries();
    if(chart->axisX() != nullptr){
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    }
    QBarSet *setMath = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoEnglish)->text());
    QLineSeries *lineSeries = new QLineSeries;
    QPen pen;
    pen.setColor(Qt::red);
    lineSeries->setPen(pen);

    for(int i = 0;i<m_pTheModel->rowCount();++i){
        setMath->append(m_pTheModel->item(i,colNoMath)->text().toInt());
        setChinese->append(m_pTheModel->item(i,colNoChinese)->text().toInt());
        setEnglish->append(m_pTheModel->item(i,colNoEnglish)->text().toInt());
        lineSeries->append(QPointF(i,m_pTheModel->item(i,colNoAverage)->text().toFloat()));
    }

    QBarSeries * series = new QBarSeries;
    series->append(setMath);
    series->append(setChinese);
    series->append(setEnglish);

    chart->addSeries(series);
    chart->addSeries(lineSeries);
    QBarCategoryAxis *axisX  = new QBarCategoryAxis;
    QStringList categroy;
    for(int i = 0;i<m_pTheModel->rowCount();i++){
        categroy<<m_pTheModel->item(i,colNoName)->text();
    }
    axisX->setCategories(categroy);
    chart->setAxisX(axisX,series);
    chart->setAxisX(axisX,lineSeries);

    QValueAxis* axisY = new QValueAxis;
    axisY->setRange(0,100);
    axisY->setTitleText("分数");
    chart->setAxisY(axisY,series);
    chart->setAxisY(axisY,lineSeries);

    chart->legend()->setAlignment(Qt::AlignBottom);







}

void MainWindow::initPieChart()
{
    QChart *chart = ui->chartViewPie->chart();
    chart->setTitle("PieChart");
    chart->setAnimationOptions(QChart::GridAxisAnimations);
    ui->chartViewPie->setRenderHint(QPainter::Antialiasing);

}

void MainWindow::buildPieChart()
{
    QChart *chart = ui->chartViewPie->chart();
    chart->removeAllSeries();
    if(chart->axisX()!= nullptr){
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    }
    QPieSeries *series = new QPieSeries;
    series->setHoleSize(ui->spinHoleSize->value());
    series->setPieSize(ui->spinPieSize->value());

    int colNo = ui->cBoxCourse->currentIndex()+1;
    QPieSlice* slice;
    for(int i = 0;i<5;++i){
        series->append(ui->treeWidget->topLevelItem(i)->text(0),ui->treeWidget->topLevelItem(i)->text(colNo).toInt());
        //        slice = series->slices().at(i);
        //        slice->setLabel(slice->label()+QString::asprintf(""
        //                                                         "%.0f,%.1f",slice->value(),slice->percentage()));
    }
    for(int i = 0;i<5;++i){

        slice = series->slices().at(i);
        slice->setLabel(slice->label()+QString::asprintf(""
                                                         "%.0f人,%.1f",slice->value(),slice->percentage()));
        connect(slice,SIGNAL(hovered(bool)),this,SLOT(ON_SliceHighLight(bool)));
    }
    chart->setTitle("PieChart---"+ui->cBoxCourse->currentText());
    chart->legend()->setAlignment(Qt::AlignRight);

    chart->addSeries(series);

}

void MainWindow::initStackedBarChart()
{
    QChart *chart= ui->chartViewStackedBar->chart();
    chart->setTitle("StackedBarChart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewStackedBar->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::buildStackedBarChart()
{
    QChart* chart = ui->chartViewStackedBar->chart();
    QStackedBarSeries *secrie = new QStackedBarSeries;
    chart->removeAllSeries();
    if(chart->axisX()!=nullptr){
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    }
    QBarSet *setMath = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoEnglish)->text());
    secrie->append(setMath);
    secrie->append(setChinese);
    secrie->append(setEnglish);

    QStringList category;
    for(int i = 0;i<m_pTheModel->rowCount();++i){
        category<<m_pTheModel->item(i,colNoName)->text();
        setMath->append(m_pTheModel->item(i,colNoMath)->text().toFloat());
        setChinese->append(m_pTheModel->item(i,colNoChinese)->text().toFloat());
        setEnglish->append(m_pTheModel->item(i,colNoEnglish)->text().toFloat());
    }
    QBarCategoryAxis* axisX = new QBarCategoryAxis;
    axisX->setCategories(category);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,300);
    axisY->setTitleText("总分");
    chart->setAxisX(axisX,secrie);
    chart->setAxisY(axisY,secrie);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chart->addSeries(secrie);
}

void MainWindow::initPrecentChart()
{
    QChart* chart = ui->chartViewPercentBar->chart();
    chart->setTitle("PrecentChart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewPercentBar->setRenderHint(QPainter::Antialiasing);


}

void MainWindow::buildPrecentChart()
{
    QChart *chart = ui->chartViewPercentBar->chart();
    chart->removeAllSeries();
    if(chart->axisX()!=nullptr){
        chart->removeAxis(chart->axisX());
        chart->removeAxis(chart->axisY());
    }
    QPercentBarSeries *secrie = new QPercentBarSeries;

    QBarSet *setMath = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoMath)->text());
    QBarSet *setChinese = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoChinese)->text());
    QBarSet *setEnglish = new QBarSet(m_pTheModel->horizontalHeaderItem(colNoEnglish)->text());
    secrie->append(setMath);
    secrie->append(setChinese);
    secrie->append(setEnglish);
    secrie->setLabelsVisible(true);//显示百分比

    QStringList category;
    for(int i = 0;i<5;++i){
        category<<ui->treeWidget->topLevelItem(i)->text(0);
        setMath->append(ui->treeWidget->topLevelItem(i)->text(1).toFloat());
        setChinese->append(ui->treeWidget->topLevelItem(i)->text(2).toFloat());
        setEnglish->append(ui->treeWidget->topLevelItem(i)->text(3).toFloat());
    }
    QBarCategoryAxis* axisX = new QBarCategoryAxis;
    axisX->setCategories(category);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,100);
    axisY->setTitleText("百分比");

    chart->setAxisX(axisX,secrie);
    chart->setAxisY(axisY,secrie);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chart->addSeries(secrie);
}

void MainWindow::initScatterChart()
{
    QChart *chart = ui->chartViewScatter->chart();
    chart->setTitle("SCatterChart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    ui->chartViewScatter->setRenderHint(QPainter::Antialiasing);

}

void MainWindow::buildScatterChart()
{
   QChart *chart = ui->chartViewScatter->chart();
   chart->removeAllSeries();
   if(chart->axisX()!=nullptr){
       chart->removeAxis(chart->axisX());
       chart->removeAxis(chart->axisY());
   }
   QScatterSeries *series =new QScatterSeries;
   QSplineSeries *Spline = new QSplineSeries;
   series->setName("Scatter");
   series->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
   Spline->setName("LineSeries");
   qreal x,y;
   for(int i = 0 ;i<15;++i){
       x= qrand()%20;
       y= qrand()%20;
       series->append(x,y);
       Spline->append(x,y);
   }

   //使用此方法setRange与rand值冲突
//   QValueAxis *axisX = new QValueAxis;
//   QValueAxis *axisY = new QValueAxis;


//   chart->setAxisX(axisX,series);

//   chart->setAxisY(axisY,series);
//   chart->setAxisX(axisX,Spline);
//   chart->setAxisY(axisY,Spline);


   chart->addSeries(series);
   chart->addSeries(Spline);

   //以下代码必须放在addSeries之后
   chart->createDefaultAxes();
   chart->axisX()->setRange(-2,22);
   chart->axisY()->setRange(-2,22);
   chart->axisX()->setTitleText("X轴");
   chart->axisY()->setTitleText("Y轴");
}


void MainWindow::on_actTongJi_triggered()
{
    SurveyData();
}


void MainWindow::on_actGenData_triggered()
{
    PrepareData();
}


void MainWindow::on_btnBuildBarChart_clicked()
{
    buildBarChart();
}


void MainWindow::on_btnDrawPieChart_clicked()
{
    buildPieChart();
}

void MainWindow::ON_SliceHighLight(bool show)
{
    QPieSlice* slice = (QPieSlice*)sender();
    slice->setExploded(show);
}


void MainWindow::on_spinHoleSize_valueChanged(double arg1)
{
    QPieSeries *series = (QPieSeries*)ui->chartViewPie->chart()->series().at(0);
    series->setHoleSize(arg1);
}


void MainWindow::on_spinPieSize_valueChanged(double arg1)
{
    QPieSeries *series = (QPieSeries*)ui->chartViewPie->chart()->series().at(0);
    series->setPieSize(arg1);
}


void MainWindow::on_cBoxTheme_activated(int index)
{
    ui->chartViewPie->chart()->setTheme(QChart::ChartTheme(index));
}


void MainWindow::on_btnBuildStackedBar_clicked()
{
    buildStackedBarChart();
}


void MainWindow::on_btnPercentBar_clicked()
{
    buildPrecentChart();
}


void MainWindow::on_btnScatter_clicked()
{
    buildScatterChart();
}

