#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(Qt::white);
    setAutoFillBackground(true);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    qreal r = 100;
    qreal deg = 3.14159*(360/5)/180;
    QPoint ponits[5] = {
        QPoint(r,0),
        QPoint(r*std::cos(deg),-r*std::sin(deg)),
        QPoint(r*std::cos(2*deg),-r*std::sin(2*deg)),
        QPoint(r*std::cos(3*deg),-r*std::sin(3*deg)),
        QPoint(r*std::cos(4*deg),-r*std::sin(4*deg))
    };

    QPainterPath startPath;
    startPath.moveTo(ponits[3]);
    startPath.lineTo(ponits[1]);
    startPath.lineTo(ponits[4]);
    startPath.lineTo(ponits[2]);
    startPath.lineTo(ponits[0]);
    startPath.closeSubpath();
    QFont font;
    font.setPointSize(12);
    //painter.setFont(font);
    startPath.addText(ponits[0],font,"0");
    startPath.addText(ponits[1],font,"1");
    startPath.addText(ponits[2],font,"2");
    startPath.addText(ponits[3],font,"3");
    startPath.addText(ponits[4],font,"4");
    //startPath.addText(QPoint(0,0),font,"S1");

    painter.setFont(font);

    painter.save();
    painter.translate(100,120);
    painter.drawPath(startPath);
    painter.drawText(0,0,"S1");


    painter.restore();
    painter.translate(300,120);
    painter.drawText(0,0,"S2");
    painter.scale(0.8,0.8);
    painter.rotate(90);
    painter.drawPath(startPath);
    //painter.drawPolygon(ponits,5);

    painter.resetTransform();
    painter.translate(500,120);
    painter.drawText(0,0,"S3");
    painter.scale(1.2,1.2);
    painter.rotate(-50);
    painter.drawPath(startPath);


}

