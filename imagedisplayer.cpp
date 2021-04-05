#include "imagedisplayer.h"

ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent)
{
}
void ImageDisplayer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(this->rect(),m_image);
}

void ImageDisplayer::linkImage(QImage image){
    m_image = image;
    this->setFixedSize(512,512);
    update();
}
