#include "fenetre.h"

Fenetre::Fenetre(){
    //m_imgD = new ImageDisplayer(this);
    this->setFixedSize(512,512);
    update();
}

Fenetre::~Fenetre()
{
}
void Fenetre::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawImage(this->rect(),m_dcm.m_image);
}

