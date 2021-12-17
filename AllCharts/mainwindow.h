#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include <QMainWindow>
#include <QStandardItemModel>

#define fixedColumnCount 5
#define iniDataRowCount 10
#define colNoName 0
#define colNoMath 1
#define colNoChinese 2
#define colNoEnglish 3
#define colNoAverage 4


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
    void on_actTongJi_triggered();

    void on_actGenData_triggered();

    void on_btnBuildBarChart_clicked();

    void on_btnDrawPieChart_clicked();

    void ON_SliceHighLight(bool show);

    void on_spinHoleSize_valueChanged(double arg1);

    void on_spinPieSize_valueChanged(double arg1);

    void on_cBoxTheme_activated(int index);

    void on_btnBuildStackedBar_clicked();

    void on_btnPercentBar_clicked();

    void on_btnScatter_clicked();

private:
    void PrepareData();
    void SurveyData();

    void initBarChart();
    void buildBarChart();

    void initPieChart();
    void buildPieChart();

    void initStackedBarChart();
    void buildStackedBarChart();

    void initPrecentChart();
    void buildPrecentChart();

    void initScatterChart();
    void buildScatterChart();

private:
    Ui::MainWindow *ui;

    QChart     *m_pChart;
    QStandardItemModel * m_pTheModel;
};
#endif // MAINWINDOW_H
