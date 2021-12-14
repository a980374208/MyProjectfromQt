#ifndef QMYGRAPHICSVIEW_H
#define QMYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>

class QMyGraphicsView : public QGraphicsView
{
    Q_OBJECT

signals:
    void mousePress(QPoint * point);
    void mouseDoubleClick(QPoint * point);
    void keyPress(QKeyEvent *event);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    //void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    //void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;



public:
    explicit QMyGraphicsView(QWidget *parent = nullptr);

signals:

};

#endif // QMYGRAPHICSVIEW_H
