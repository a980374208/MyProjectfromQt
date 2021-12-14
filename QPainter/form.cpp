#include "form.h"
#include "ui_form.h"
#include <QPainter>

void Form::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int W = width();
    int H = height();

    //painter.setRenderHints(QPainter::TextAntialiasing|painter::Antialiasing);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(20);
    pen.setStyle(Qt::DashDotLine);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::Dense1Pattern);
    painter.setBrush(brush);

    QRect rect(W/4,H/4,W/2,H/2);
//    QImage image(":/images/images/qt.jpg");
//    painter.drawImage(rect,image);
//    QFont font;
//    font.setPointSize(30);
//    painter.setFont(font);
//    painter.drawText(rect,"Hello Word");
    //painter.drawRect(rect);

    QPoint ponit[]= {QPoint(W/3,H/3),QPoint(W/2,H/2),QPoint(W/2,2*H/2)};
    painter.drawPolyline(ponit,3);

}

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
}

Form::~Form()
{
    delete ui;
}
