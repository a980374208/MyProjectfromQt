#ifndef QMYCHARTVIEW_H
#define QMYCHARTVIEW_H
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

#include <QWidget>
#include <QPoint>

class QMyChartView : public QChartView
{
    Q_OBJECT
protected:
    QPoint beginPoint;
    QPoint endPoint;


protected:

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

public:
    explicit QMyChartView(QWidget *parent = nullptr);

signals:
    SendPoint(QPoint *point);

};

#endif // QMYCHARTVIEW_H
