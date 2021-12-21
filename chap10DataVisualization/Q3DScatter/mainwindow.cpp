#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

void MainWindow::initScatter()
{
    m_pGraphics = new Q3DScatter;

    QScatterDataProxy *proxy = new QScatterDataProxy;
    QScatter3DSeries *series = new QScatter3DSeries(proxy);
    //series->setMesh(QAbstract3DSeries::MeshCylinder);
    //series->setItemLabelFormat("(@X @Y @Z)");
    series->setItemLabelFormat("(@xLabelx @yLabely @zLabelz)");
    QScatterDataArray *scatterArray = new QScatterDataArray;

    m_pGraphics->axisX()->setTitle("X轴");
    m_pGraphics->axisY()->setTitle("Y轴");
    series->setItemSize(0.2);

    int N = 41;
    scatterArray->resize(N*N);
    QScatterDataItem* scatterItem = &scatterArray->first();



    float x,y,z;
    x=-10;
    for(int i = 1;i<=N;++i){
        y=-10;
        for(int j= 1;j<=N;++j){
           z = qSqrt(x*x+y*y);
           if(z!=0)
               z = 10*qSin(z)/z;
           else
               z = 10;
           scatterItem->setPosition(QVector3D(x,z,y));
           scatterItem++;
           y+=0.5;
        }
        x+=0.5;
    }
    series->dataProxy()->resetArray(scatterArray);
    m_pGraphics->addSeries(series);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(ui->groupBox);
    initScatter();
    splitter->addWidget(createWindowContainer(m_pGraphics));
    setCentralWidget(splitter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

