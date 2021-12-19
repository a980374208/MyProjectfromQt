#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

void MainWindow::initLandform()
{
    m_plandForm = new Q3DSurface;
    m_plandForm->axisX()->setTitle("东--西");
    m_plandForm->axisY()->setTitle("高度");
    m_plandForm->axisZ()->setTitle("南--北");
    m_plandForm->axisX()->setTitleVisible(true);
    m_plandForm->axisY()->setTitleVisible(true);
    m_plandForm->axisZ()->setTitleVisible(true);
    m_plandForm->axisX()->setLabelFormat("%.1f米");
    QImage heightMapImage(":/map/sea.png");
    m_pLandformProxy = new QHeightMapSurfaceDataProxy(heightMapImage);
    m_pLandformProxy->setValueRanges(-5000,5000,-5000,5000);

    m_pLandformSeries = new QSurface3DSeries(m_pLandformProxy);
    m_pLandformSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    m_plandForm->addSeries(m_pLandformSeries);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSplitter* splitter = new QSplitter;
    splitter->addWidget(ui->groupBox);
    initLandform();
    splitter->addWidget(createWindowContainer(m_plandForm));
    setCentralWidget(splitter);



    QLinearGradient grBtoY(0, 0, 100, 0);
    grBtoY.setColorAt(1.0, Qt::black);
    grBtoY.setColorAt(0.67, Qt::blue);
    grBtoY.setColorAt(0.33, Qt::red);
    grBtoY.setColorAt(0.0, Qt::yellow);

    QPixmap pm(160, 20);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(grBtoY));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 160, 20);
    ui->btnGrad1->setIcon(QIcon(pm));
    ui->btnGrad1->setIconSize(QSize(160, 20));

    QLinearGradient grGtoR(0, 0, 100, 0);
//    grGtoR.setColorAt(0.0, Qt::darkGreen);
//    grGtoR.setColorAt(0.2, Qt::yellow);
//    grGtoR.setColorAt(0.5, Qt::red);
//    grGtoR.setColorAt(1.0, Qt::darkRed);
    grGtoR.setColorAt(1.0, Qt::darkGreen);
    grGtoR.setColorAt(0.5, Qt::yellow);
    grGtoR.setColorAt(0.2, Qt::red);
    grGtoR.setColorAt(0.0, Qt::darkRed);
    pmp.setBrush(QBrush(grGtoR));
    pmp.drawRect(0, 0, 160, 20);
    ui->btnGrad2->setIcon(QIcon(pm));
    ui->btnGrad2->setIconSize(QSize(160, 20));

}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{
    QAbstract3DSeries::Mesh aMesh;
    aMesh=QAbstract3DSeries::Mesh(index+1);
    m_pLandformSeries->setMesh(aMesh);
}


void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{
    //m_plandForm->setSelectionMode(QAbstract3DGraph::SelectionFlag(index));
    switch(index)
    {
     case 0:    //none
        m_plandForm->setSelectionMode(QAbstract3DGraph::SelectionNone);
        break;
     case 1:    //Item
        m_plandForm->setSelectionMode(QAbstract3DGraph::SelectionItem);
        break;
     case 2:    //Row Slice
        m_plandForm->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                  | QAbstract3DGraph::SelectionSlice);
        break;
     case 3:    //Column Slice
        m_plandForm->setSelectionMode(QAbstract3DGraph::SelectionItemAndColumn
                                 | QAbstract3DGraph::SelectionSlice);
    default:
        break;

    }
}


void MainWindow::on_comboDrawMode_currentIndexChanged(int index)
{
    if (index==0)
        m_pLandformSeries->setDrawMode(QSurface3DSeries::DrawWireframe);
    else if (index==1)
        m_pLandformSeries->setDrawMode(QSurface3DSeries::DrawSurface);
    else
        m_pLandformSeries->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
}
#include <QColorDialog>

void MainWindow::on_btnBarColor_clicked()
{
    QColor  color=m_pLandformSeries->baseColor();
    color=QColorDialog::getColor(color);
    if (color.isValid())
    {
        m_pLandformSeries->setBaseColor(color);
        m_pLandformSeries->setColorStyle(Q3DTheme::ColorStyleUniform);
    }
}


void MainWindow::on_btnGrad1_clicked()
{
    QLinearGradient grGtoR;
    grGtoR.setColorAt(1.0, Qt::black);
    grGtoR.setColorAt(0.67, Qt::blue);
    grGtoR.setColorAt(0.33, Qt::red);
    grGtoR.setColorAt(0.0, Qt::yellow);

    m_pLandformSeries->setBaseGradient(grGtoR);
    m_pLandformSeries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}


void MainWindow::on_btnGrad2_clicked()
{
    QLinearGradient grGtoR;
    grGtoR.setColorAt(1.0, Qt::darkGreen);
    grGtoR.setColorAt(0.5, Qt::yellow);
    grGtoR.setColorAt(0.2, Qt::red);
    grGtoR.setColorAt(0.0, Qt::darkRed);

    m_pLandformSeries->setBaseGradient(grGtoR);
    m_pLandformSeries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    m_plandForm->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}


void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    m_plandForm->activeTheme()->setType(Q3DTheme::Theme(index));
}

