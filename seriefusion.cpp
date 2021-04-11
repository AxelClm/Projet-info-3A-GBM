#include "seriefusion.h"

SerieFusion::SerieFusion(QWidget* parent) : Series(parent)
{
    m_parent = parent;
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
    QVector<QImage*> res = rescale(a,b);
    a = res.at(0);
    b = res.at(1);
    return fusion(a,b);
}
QImage* SerieFusion::fusion(QImage*a,QImage*b){
    double ratio = 0.5;
    int pt1 = 85;
    int pt2 = 170;
    QImage* c = new QImage(a->width(),a->height(),QImage::Format_RGB16);
    for(int y = 0 ; y<a->height() ; y++){
        for(int x=0;x<a->width();x++){
            QColor pixa = a->pixelColor(x,y);
            QColor pixb = b->pixelColor(x,y);
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
                color.setBlue(255);
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

QVector<QImage*> SerieFusion::rescale(QImage*a,QImage*b){
    double xa =-249.51;
    double ya =-418.51;
    double xas = 0.976;
    double yas = 0.976;
    double xb = -342.13/2.23;
    double yb = -509.6/1.6;
    double xbs = 2.08;
    double ybs = 2.08;
    bool achanged = false;
    bool bchanged = false;

    qreal distx = qFabs(xa)-qFabs(xb);
    qreal disty = qFabs(ya)-qFabs(yb);
    qDebug()<<distx <<" "<<disty;
    if(distx<0){//a est donc plus eloigné
        int nbrPix = qFabs(distx/xas);
        a = removeX(a,nbrPix);
        achanged = true;
    }
    else{
        int nbrPix=qFabs(distx/xbs);
        b = removeX(b,nbrPix);
        bchanged =true;
    }
    if(disty<0){//A est plus eloigné
        int nbrPix = qFabs(disty/yas);
        a= removeY(a,nbrPix);
        achanged = true;
    }
    else{
        int nbrPix = qFabs(disty/ybs);
        b=removeY(b,nbrPix);
        bchanged =true;
    }
    //On a donc les images au même 0.
    //Il faut maintenant qu'elles s'arretent au même endroit
    distx = (a->width()*xas) - (b->width()*xbs);
    disty = (a->height()*yas) - (b->height()*ybs);
    qDebug() << distx <<" " <<disty;
    if(distx < 0){ //b est alors plus grands.
        int nbrPix = qFabs(distx)/xbs;
        qDebug() <<"b"<<nbrPix;
        QImage* tmp = removeXL(b,nbrPix);
        if(bchanged==true){
            delete b;
        }
        b = tmp;
        bchanged =true;
    }
    else{
        int nbrPix = qFabs(distx)/xas;
        qDebug() << nbrPix;
        QImage* tmp = removeXL(a,nbrPix);
        if(achanged==true){
            delete a;
        }
        a = tmp;
        achanged =true;
    }
    if(distx < 0){ //b est alors plus grands.
        int nbrPix = qFabs(disty)/ybs;
        qDebug() <<"b"<<nbrPix;
        QImage* tmp = removeYL(b,nbrPix);
        if(bchanged==true){
            delete b;
        }
        b = tmp;
        bchanged =true;
    }
    else{
        int nbrPix = qFabs(disty)/yas;
        qDebug() << nbrPix;
        QImage* tmp = removeYL(a,nbrPix);
        if(achanged==true){
            delete a;
        }
        a = tmp;
        achanged =true;
    }
    qDebug() << "taille";
    qDebug() <<a->width() << " " << a->height();
    qDebug() <<b->width() << " " << b->height();
    //On remet maintenant a et b a la meme taille;
    if(a->width() > b->width()){
        QImage* tmp = new QImage(b->scaled(a->width(),a->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        if(bchanged == true){
            delete b;
        }
        b = tmp;
    }
    else{
        QImage* tmp = new QImage(a->scaled(b->width(),b->height(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        if(achanged == true){
            delete a;
        }
        a = tmp;
    }
    qDebug() << "taille f";
    qDebug() <<a->width() << " " << a->height();
    qDebug() <<b->width() << " " << b->height();
    QVector<QImage*> res;
    res.append(a);
    res.append(b);
    return res;
}
QImage* SerieFusion::removeX(QImage* a, int nbrX){
    QImage*c = new QImage(a->width()-nbrX,a->height(),QImage::Format_Grayscale16);
    for(int y=0;y<a->height();y++){
        for(int x=nbrX;x<a->width();x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x-nbrX,y,color);
        }
    }
    return c;

}
QImage* SerieFusion::removeY(QImage* a, int nbrY){
    QImage*c = new QImage(a->width(),a->height()-nbrY,QImage::Format_Grayscale16);
    for(int y=nbrY;y<a->height();y++){
        for(int x=0;x<a->width();x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x,y-nbrY,color);
        }
    }
    return c;

}
QImage* SerieFusion::removeYL(QImage* a, int nbrY){
    QImage*c = new QImage(a->width(),a->height()-nbrY,QImage::Format_Grayscale16);
    for(int y=0;y<a->height()-nbrY;y++){
        for(int x=0;x<a->width();x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x,y,color);
        }
    }
    return c;

}
QImage* SerieFusion::removeXL(QImage* a, int nbrX){
    QImage*c = new QImage(a->width()-nbrX,a->height(),QImage::Format_Grayscale16);
    for(int y=0;y<a->height();y++){
        for(int x=0;x<a->width()-nbrX;x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x,y,color);
        }
    }
    return c;

}
void SerieFusion::InitialisationImages(){
    int t =1;
    QProgressDialog progress("Generation des Images","Annuler",0,m_s1->getMax(),m_parent);
    progress.setWindowModality(Qt::WindowModal);
    for(int i=0;i<m_s1->getMax();i++){
       QVector<QImage*> res = rescale(m_s1->getIndex(i),m_s2->getIndex(i));
       m_liste.append(fusion(res.at(0),res.at(1)));
       progress.setValue(t);
    }
}
QImage* SerieFusion::getIndex(int i){
    return m_liste.at(i);
}
int SerieFusion::getMax(){
    return m_liste.size();
}
