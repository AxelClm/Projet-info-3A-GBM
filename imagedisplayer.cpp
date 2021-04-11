#include "imagedisplayer.h"

ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent)
{
    m_image = NULL;
}
void ImageDisplayer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if(m_image != NULL){
        painter.drawImage(this->rect(),*m_image);
    }
}

void ImageDisplayer::linkImage(QImage* image){
    m_image = image;
    update();
}
void ImageDisplayer::changerS(int width){
    this->setFixedSize(width,width);
    update();
}
