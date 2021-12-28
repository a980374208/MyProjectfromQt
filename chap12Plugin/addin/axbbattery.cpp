#include "axbbattery.h"
#include <QPainter>
void AXBBattery::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect rect(0,0,width(),height());
    painter.setViewport(rect);
    painter.setWindow(0,0,120,50);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    QPen pen;
    pen.setWidth(2);
    pen.setColor(mColorBorder);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);

    painter.setPen(pen);
    QBrush brush;
    brush.setColor(mColorBack);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    rect.setRect(1,1,109,48);
    painter.drawRect(rect);
    painter.drawRect(rect);
    //brush.setColor(mColorBack);
    painter.setBrush(brush);
    rect.setRect(110,15,10,20);
    painter.drawRect(rect);

    //画殿亮
    if(mPowreLeve <= mWarning){
        brush.setColor(mColorWarning);
        pen.setColor(mColorWarning);
    }else{
        brush.setColor(mColorPower);
        pen.setColor(mColorPower);
    }
    painter.setBrush(brush);
    painter.setPen(pen);

    if(mPowreLeve>0){
        rect.setRect(5,5,mPowreLeve,40);
        painter.drawRect(rect);
    }
    if(mPowreLeve == 100){
        rect.setRect(5,5,mPowreLeve,40);
        painter.drawRect(rect);
        rect.setRect(113,18,4,14);
        painter.drawRect(rect);
    }

    //绘制电量显示文本
    QFontMetrics textSize(this->font());
    QString powStr = QString::asprintf("%d%%",mPowreLeve);
    QRect textRect = textSize.boundingRect(powStr);
    pen.setColor(mColorBorder);
    painter.setPen(pen);
    painter.drawText(55-textRect.width()/2,
                     23+textRect.height()/2,powStr);//1:左上角x  2:左上角y

}

void AXBBattery::setPowerLeve(int powerLeve)
{
    mPowreLeve = powerLeve;
        repaint();
}

int AXBBattery::powerLeve() const
{
    return mPowreLeve;

}

AXBBattery::AXBBattery(QWidget *parent) : QWidget(parent)
{

}
