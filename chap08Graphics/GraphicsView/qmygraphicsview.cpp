#include "qmygraphicsview.h"


QMyGraphicsView::QMyGraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

void QMyGraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit keyPress(event);
    return QGraphicsView::keyPressEvent(event);
}

void QMyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button()){
        QPoint piont = event->pos();
        emit mouseDoubleClick(&piont);
    }
    return QGraphicsView::mouseDoubleClickEvent(event);

}

void QMyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button()){
        QPoint point = event->pos();
        emit mousePress(&point);
    }
    return QGraphicsView::mousePressEvent(event);
}


