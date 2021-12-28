#ifndef AXBBATTERY_H
#define AXBBATTERY_H

#include <QWidget>
#include <QColor>

class AXBBattery : public QWidget
{
    Q_OBJECT

private:
    QColor mColorBack = Qt::white;
    QColor mColorBorder = Qt::black;
    QColor mColorPower = Qt::green;
    QColor mColorWarning = Qt::red;
    int mPowreLeve = 50;
    int mWarning = 20;

public:
    void paintEvent(QPaintEvent *event)Q_DECL_OVERRIDE;

    void setPowerLeve(int powerLeve);

    int powerLeve() const;

public:
    explicit AXBBattery(QWidget *parent = nullptr);

signals:

};

#endif // AXBBATTERY_H
