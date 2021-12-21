#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QLinearGradient>


void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    int W = width();
    int H = height();
    painter.setRenderHint(QPainter::Antialiasing);
    int side = qMin(W,H);
    QRect rect((W-side)/2,(H-side)/2,side,side);
    painter.drawRect(rect);
    painter.setViewport(rect);

    painter.setWindow(-100,-100,200,200);

    QLinearGradient linearGrad(0,0,100,0);
    linearGrad.setColorAt(0,Qt::yellow);
    linearGrad.setColorAt(1,Qt::green);
    //linearGrad.setSpread(QGradient::PadSpread);

    painter.setBrush(linearGrad);

    painter.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
    //painter.setCompositionMode(QPainter::RasterOp_NotSourceAndNotDestination);
    for(int i = 0;i<36;++i){
        painter.drawEllipse(QPoint(50,0),50,50);
        painter.rotate(10);
    }


}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(Qt::white);
    setAutoFillBackground(true);
    resize(300,300);
}

Widget::~Widget()
{
    delete ui;
}

