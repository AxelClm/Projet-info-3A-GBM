#include "imagedisplayer.h"

ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent)
{
            bool loaded = m_image.load(("C:/Users/Utilisateur/Documents/Cours/Polytech/POOW/ProjetGBM/PET.BMP"));
            if(loaded){
                this->setFixedSize(300,300);
            }
}
void ImageDisplayer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(this->rect(),m_image);
}
