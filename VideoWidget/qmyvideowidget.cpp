#include "qmyvideowidget.h"

QmyVideowidget::QmyVideowidget(QWidget *parent) : QVideoWidget(parent)
{

}

void QmyVideowidget::setMediaPlayer(QMediaPlayer *player)
{
   m_pThePlayer = player;
}
