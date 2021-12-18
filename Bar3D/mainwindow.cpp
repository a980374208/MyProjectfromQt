#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSplitter>

void MainWindow::initChart3D()
{
    m_pChart3D = new Q3DBars;
    QValue3DAxis *axisVa = new QValue3DAxis;
    axisVa->setTitle("Value");
    axisVa->setTitleVisible(true);

    QCategory3DAxis* axisRow = new QCategory3DAxis;
    QCategory3DAxis* axisCol = new QCategory3DAxis;
    axisCol->setTitle("Column");
    axisRow->setTitle("row");
    axisCol->setTitleVisible(true);
    axisCol->setTitleVisible(true);

    QStringList RowLabs,ColLabs;
    RowLabs<<"row1"<<"row2"<<"row3";
    ColLabs<<"col1"<<"col2"<<"col3"<<"col4"<<"col5"<<"col6";
    axisCol->setLabels(ColLabs);
    axisRow->setLabels(RowLabs);

    m_pChart3D->setValueAxis(axisVa);
    m_pChart3D->setRowAxis(axisRow);
    m_pChart3D->setColumnAxis(axisCol);


}

void MainWindow::PrepareData()
{
    QBar3DSeries *series = new QBar3DSeries;
    series->setMesh(QAbstract3DSeries::MeshCone);
    series->setItemLabelFormat("(@rowLabel,@colLabel):%.1f");
    m_pChart3D->addSeries(series);

    QBarDataArray *dataSet = new QBarDataArray;
    int RowLabs = m_pChart3D->rowAxis()->labels().count();
    dataSet->reserve(RowLabs); //可不设置但影响效率且后续添加数据较多添加过程中可能崩溃
    QBarDataRow *dataRow0 = new QBarDataRow;
    *dataRow0<<1<<2<<3<<4<<5<<6;
    QBarDataRow *dataRow1 = new QBarDataRow;
    *dataRow1<<2<<2<<2<<2<<5<<5;
    QBarDataRow *dataRow2 = new QBarDataRow;
    *dataRow2<<6<<5<<4<<4<<5<<6;
    dataSet->append(dataRow0);
    dataSet->append(dataRow1);
    dataSet->append(dataRow2);

    series->dataProxy()->resetArray(dataSet);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    splitter->addWidget(ui->groupBox);
    setCentralWidget(splitter);
    initChart3D();
    PrepareData();

   splitter->addWidget(createWindowContainer(m_pChart3D));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboCamera_activated(int index)
{
    m_pChart3D->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}


void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot =ui->sliderH->value();//水平
    int yRot=ui->sliderV->value(); //垂直
    int zoom=ui->sliderZoom->value(); //缩放
    m_pChart3D->scene()->activeCamera()->setCameraPosition(xRot, yRot,zoom);
}


void MainWindow::on_sliderV_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}


void MainWindow::on_sliderZoom_valueChanged(int value)
{
    on_sliderH_valueChanged(value);
}


void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    m_pChart3D->activeTheme()->setType(Q3DTheme::Theme(index));
}


void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{
    QBar3DSeries *series = m_pChart3D->seriesList().at(0);
    series->setMesh(QAbstract3DSeries::Mesh(index+1));
    //MeshUserDefined = 0,
}


void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{
    m_pChart3D->setSelectionMode(QAbstract3DGraph::SelectionFlag(index));

}

#include <QFontDialog>
void MainWindow::on_spinFontSize_valueChanged(int arg1)
{
    QFont font= m_pChart3D->activeTheme()->font();
    font.setPointSize(arg1);
    m_pChart3D->activeTheme()->setFont(font);
}

#include <QColorDialog>
void MainWindow::on_btnBarColor_clicked()
{
    QBar3DSeries *series = m_pChart3D->seriesList().at(0);
    QColor color = series->baseColor();
    color = QColorDialog::getColor(color);
    if(color.isValid())
        series->setBaseColor(color);
}


void MainWindow::on_chkBoxBackground_clicked(bool checked)
{
    m_pChart3D->activeTheme()->setBackgroundEnabled(checked);
}


void MainWindow::on_chkBoxGrid_clicked(bool checked)
{
    m_pChart3D->activeTheme()->setGridEnabled(checked);
}


void MainWindow::on_chkBoxSmooth_clicked(bool checked)
{
    QBar3DSeries *series = m_pChart3D->seriesList().at(0);
    series->setMeshSmooth(checked);
}


void MainWindow::on_chkBoxReflection_clicked(bool checked)
{
    m_pChart3D->setReflection(checked);
}


void MainWindow::on_chkBoxReverse_clicked(bool checked)
{

    m_pChart3D->valueAxis()->setReversed(checked);
}


void MainWindow::on_chkBoxItemLabel_clicked(bool checked)
{
    QBar3DSeries *series = m_pChart3D->seriesList().at(0);
    series->setItemLabelVisible(checked);
}


void MainWindow::on_chkBoxAxisTitle_clicked(bool checked)
{
    m_pChart3D->valueAxis()->setTitleVisible(checked);
    m_pChart3D->rowAxis()->setTitleVisible(checked);
    m_pChart3D->columnAxis()->setTitleVisible(checked);
}


void MainWindow::on_chkBoxAxisBackground_clicked(bool checked)
{
    m_pChart3D->activeTheme()->setLabelBackgroundEnabled(checked);
}




