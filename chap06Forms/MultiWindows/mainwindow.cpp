#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->setVisible(false);
    //setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <QPainter>
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->toolBar->height(),width(),
                       height()-ui->toolBar->height()-ui->statusbar->height(),
                       QPixmap(":\\images\\images\\back2.jpg"));

}


void MainWindow::on_actWindowInsite_triggered()
{


}


void MainWindow::on_actWidgetInsite_triggered()
{
    FormDoc *formDoc = new FormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formDoc,QString::asprintf("Doc %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(ui->tabWidget->count() == 1){
        ui->tabWidget->setVisible(false);
    }
    if(index<0) return;
    QWidget* tab = ui->tabWidget->widget(index);
    tab->close();

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    bool en = ui->tabWidget->count()>0;
    ui->tabWidget->setVisible(en);
}


void MainWindow::on_actWidget_triggered()
{
    FormDoc *formDoc = new FormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowTitle("widget独立显示");
    formDoc->setWindowOpacity(0.7);
//    formDoc->show();
    setAttribute(Qt::WA_ShowModal, true);
    formDoc->show();
}

