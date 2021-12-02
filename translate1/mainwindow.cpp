#include "mainwindow.h"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qLabel = new QLabel(tr("English"));
    QWidget* qWidget = new QWidget;
    qLabel->setParent(qWidget);
    this->setCentralWidget(qWidget);
}

MainWindow::~MainWindow()
{
}

