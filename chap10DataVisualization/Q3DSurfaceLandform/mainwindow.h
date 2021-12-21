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
    void initLandform();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_cBoxBarStyle_currentIndexChanged(int index);

    void on_cBoxSelectionMode_currentIndexChanged(int index);

    void on_comboDrawMode_currentIndexChanged(int index);

    void on_btnBarColor_clicked();

    void on_btnGrad1_clicked();

    void on_btnGrad2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_cBoxTheme_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    Q3DSurface * m_plandForm;
    QSurface3DSeries *m_pLandformSeries;
    QHeightMapSurfaceDataProxy *m_pLandformProxy;

};
#endif // MAINWINDOW_H
