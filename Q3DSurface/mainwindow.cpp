#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

void MainWindow::initSurface()
{
    m_pSurface = new Q3DSurface;

    QSurfaceDataProxy *surfaceProxy = new QSurfaceDataProxy;//不写自动创建
    surfaceSeries = new QSurface3DSeries(surfaceProxy);
    m_pSurface->addSeries(surfaceSeries);
    surfaceSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    surfaceSeries->setMeshSmooth(true);
    surfaceArray = new QSurfaceDataArray;
    //QSurfaceDataItem* surfaceItem = surfaceArray->first(); //不能用

    //创建坐标轴
    QValue3DAxis *axisX=new QValue3DAxis;
    axisX->setTitle("Axis X");
    axisX->setTitleVisible(true);
    axisX->setRange(-11,11);
    //    axisX->setAutoAdjustRange(true);
    m_pSurface->setAxisX(axisX);

    QValue3DAxis *axisY=new QValue3DAxis;
    axisY->setTitle("Axis Y");
    axisY->setTitleVisible(true);
    //    axisY->setRange(-10,10);
    axisY->setAutoAdjustRange(true);
    m_pSurface->setAxisY(axisY);

    QValue3DAxis *axisZ=new QValue3DAxis;
    axisZ->setTitle("Axis Z");
    axisZ->setTitleVisible(true);
    axisZ->setRange(-11,11);
    //    axisZ->setAutoAdjustRange(true);
    m_pSurface->setAxisZ(axisZ);


}

void MainWindow::PrepareSurface()
{
    int N = 41;
    surfaceArray->reserve(N);

    qreal x = -10,y, z;
    for(int i = 1;i<=N;++i){
        QSurfaceDataRow *newRow = new QSurfaceDataRow(N);
        int index=0;
        y = -10;
        for(int j = 1;j<=N;++j){
            z = qSqrt(x*x+y*y);
            if(z != 0)
                z= 10*qSin(z)/z;
            else
                z = 10;
            y+=0.5;
 //        surfaceItem++;
 //        surfaceItem->setPosition(QVector3D(x,z,y));//不能用
            (*newRow)[index++].setPosition(QVector3D(x, z, y));
            *surfaceArray << newRow; //上两句等于此
        }
        x+=0.5;


    }

    surfaceSeries->dataProxy()->resetArray(surfaceArray);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSplitter* splitter = new QSplitter;
    splitter->addWidget(ui->groupBox);
    initSurface();
    PrepareSurface();
    splitter->addWidget(createWindowContainer(m_pSurface));
    setCentralWidget(splitter);


    QLinearGradient lgcolor(0,0,100,0);
    lgcolor.setColorAt(1.0,Qt::yellow);
    lgcolor.setColorAt(0.67,Qt::black);
    lgcolor.setColorAt(0.35,Qt::blue);
    lgcolor.setColorAt(0.0,Qt::gray);
    int w = ui->btnGrad1->width();
    int h = ui->btnGrad1->height();
    QPixmap pix(w,h);
    QPainter painter(&pix);
    painter.setBrush(lgcolor);
    painter.drawRect(0,0,w,h);
    ui->btnGrad1->setIcon(QIcon(pix));
    ui->btnGrad1->setIconSize(QSize(w,h));


    lgcolor.setColorAt(1.0,Qt::darkBlue);
    lgcolor.setColorAt(0.67,Qt::darkCyan);
    lgcolor.setColorAt(0.35,Qt::darkYellow);
    lgcolor.setColorAt(0.0,Qt::darkRed);
    w = ui->btnGrad2->width();
    h = ui->btnGrad2->height();
    painter.setBrush(lgcolor);
    painter.drawRect(0,0,w,h);
    ui->btnGrad2->setIcon(QIcon(pix));
    ui->btnGrad2->setIconSize(QSize(w,h));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboDrawMode_currentIndexChanged(int index)
{
    surfaceSeries->setDrawMode(QSurface3DSeries::DrawFlags(index+1));

}

#include <QColorDialog>
void MainWindow::on_btnBarColor_clicked()
{
    QColor color = surfaceSeries->baseColor();
    color = QColorDialog::getColor(color);
    if(color.isValid()){
        surfaceSeries->setBaseColor(color);
        surfaceSeries->setColorStyle(Q3DTheme::ColorStyleUniform);
    }
}


void MainWindow::on_btnGrad1_clicked()
{
    QLinearGradient lgcolor(0,0,100,0);
    lgcolor.setColorAt(1.0,Qt::yellow);
    lgcolor.setColorAt(0.67,Qt::black);
    lgcolor.setColorAt(0.35,Qt::blue);
    lgcolor.setColorAt(0.0,Qt::gray);

    surfaceSeries->setBaseGradient(lgcolor);
    surfaceSeries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}


void MainWindow::on_btnGrad2_clicked()
{
    QLinearGradient lgcolor(0,0,100,0);
    lgcolor.setColorAt(1.0,Qt::darkBlue);
    lgcolor.setColorAt(0.67,Qt::darkCyan);
    lgcolor.setColorAt(0.35,Qt::darkYellow);
    lgcolor.setColorAt(0.0,Qt::darkRed);

    surfaceSeries->setBaseGradient(lgcolor);
    surfaceSeries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

