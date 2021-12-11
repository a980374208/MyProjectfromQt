#ifndef QMYVIDEOWIDGET_H
#define QMYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QMediaPlayer>

class QmyVideowidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit QmyVideowidget(QWidget *parent = nullptr);
    void setMediaPlayer(QMediaPlayer *player);

signals:

private:
    QMediaPlayer *m_pThePlayer;

};

#endif // QMYVIDEOWIDGET_H
