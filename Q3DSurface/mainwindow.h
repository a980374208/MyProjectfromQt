#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDataVisualization>
using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void initSurface();
    void PrepareSurface();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboDrawMode_currentIndexChanged(int index);

    void on_btnBarColor_clicked();

    void on_btnGrad1_clicked();

    void on_btnGrad2_clicked();

private:
    Ui::MainWindow *ui;
    Q3DSurface * m_pSurface;
    QSurface3DSeries* surfaceSeries;
    QSurfaceDataArray* surfaceArray;


};
#endif // MAINWINDOW_H
