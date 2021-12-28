#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(ui->battery->powerLeve());

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_horizontalSlider_valueChanged(int value)
{
    ui->battery->setPowerLeve(value);
    ui->label->setText(QString::asprintf("当前点亮：%d%%",value));

}

