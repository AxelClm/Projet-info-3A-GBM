#include "seriefusion.h"

SerieFusion::SerieFusion()
{
    m_s1 = NULL;
    m_s2 = NULL;
}
void SerieFusion::ajouter(Series* s){
    if(m_s1 == NULL){
        m_s1 = s;
    }
    else if(m_s2 == NULL){
        m_s2 =s;
    }
}
QImage* SerieFusion::getFirst(){
    QImage* a = m_s1->getFirst();
    QImage* b = m_s2->getFirst();
    return fusion(a,b);
}
QImage* SerieFusion::fusion(QImage*a,QImage*b2){
    double ratio = 0.5;
    QImage b = b2->scaled(a->width(),a->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    int pt1 = 85;
    int pt2 = 170;
    QImage* c = new QImage(a->width(),a->height(),QImage::Format_RGB16);
    for(int y = 0 ; y<a->height() ; y++){
        for(int x=0;x<a->width();x++){
            QColor pixa = a->pixelColor(x,y);
            QColor pixb = b.pixelColor(x,y);
            int moy = -pixb.black() + 255;
            int moy2 = -pixa.black() +255;
            QColor color;
            if(moy<85){
               int tmp = moy2*ratio +moy*(1-ratio)*(255/pt1);
               color.setGreen(moy2*ratio);
               color.setBlue(moy2*ratio);
               if(tmp > 255){
                   color.setRed(255);
               }
               else{
                   color.setRed(tmp);
               }
               c->setPixelColor(x,y,color);
            }
            else if(moy<pt2){
                int tmp = moy2*ratio +(moy*(255/85)-255)*(1-ratio);
                color.setRed(255);
                color.setBlue(moy2*ratio);
                if(tmp > 255){
                    color.setGreen(255);
                }
                else{
                    color.setGreen(tmp);
                }
                c->setPixelColor(x,y,color);
            }
            else if (moy>pt2){
                int tmp = moy2*ratio +(moy*(255/85)-510)*(1-ratio);
                color.setRed(255);
                (255);
                if(tmp > 255){
                    color.setBlue(255);
                }
                else{
                    color.setBlue(tmp);
                }
                c->setPixelColor(x,y,color);
             }
           }
        }
    return c;
}
