#include "seriedamier.h"

SerieDamier::SerieDamier(QWidget* parent) : Series(parent)
{
    m_parent = parent;
    m_s1 = NULL;
    m_s2 = NULL;
    m_dX = 2;
    m_dY = 2;
    m_synchro = NULL;

}
SerieDamier::~SerieDamier(){

}
void SerieDamier::ajouter(Series *s){
    if(m_s1 == NULL){
        m_s1 = s;
    }
    else if(m_s2 == NULL){
        m_s2 =s;
    }
}
QImage* SerieDamier::fastRender(int index){
    if(m_synchro == NULL){
        m_synchro = new synchro(m_s1,m_s2);
    }
    int* tab = m_synchro->getIndex(index);
    QVector<QImage*> res = rescale(m_s1->getIndex(tab[0]),m_s2->getIndex(tab[1]),m_s1->getIdI(tab[0])->getX(),
            m_s1->getIdI(tab[0])->getY(),m_s1->getIdI(tab[0])->getXPix(),m_s1->getIdI(tab[0])->getYPix(),
            m_s2->getIdI(tab[1])->getX(),m_s2->getIdI(tab[1])->getY(),m_s2->getIdI(tab[1])->getXPix(),
            m_s2->getIdI(tab[1])->getYPix());
    return damier(res.at(0),res.at(1));
}
QImage* SerieDamier::damier(QImage* a, QImage* b){ //On fait juste un cadrillage
    QImage* c = new QImage(a->width(),a->height(),QImage::Format_Grayscale16);
    for(int y = 0 ; y<a->height() ; y++){
        for(int x=0;x<a->width();x++){
            if((y/(a->height()/m_dY))%2 == 0){
                if((x/(a->width()/m_dX))%2 == 0){
                    c->setPixelColor(x,y,a->pixelColor(x,y));
                }
                else{
                    c->setPixelColor(x,y,b->pixelColor(x,y));
                }
            }
            else{
                if((x/(a->width()/m_dX))%2 != 0){
                    c->setPixelColor(x,y,a->pixelColor(x,y));
                }
                else{
                    c->setPixelColor(x,y,b->pixelColor(x,y));
                }
            }
        }
    }
    return c;
}
QVector<QImage*> SerieDamier::rescale(QImage*a,QImage*b,double xa , double ya, double xas , double yas , double xb, double yb,double xbs, double ybs){
    bool achanged = false;
    bool bchanged = false;

    qreal distx = qFabs(xa)-qFabs(xb);
    qreal disty = qFabs(ya)-qFabs(yb);
    // Le  but de la fonction est de replacer l'image dans l'espace pour ensuite
    // supperposé les deux. On part evidemment du principe que les images sont prises dans
    // Le même repert (C'est le cas dans mon set donc pas besoin de faire des calculs supp)
    if(distx <0){
        int nbrPix = qFabs(distx/xbs);
        b = removeX(b,nbrPix);
        bchanged = true;
    }
    else{
        int nbrPix = qFabs(distx/xas);
        a = removeX(a,nbrPix);
        achanged = true;
    }
    if(disty < 0){
        int nbrPix = qFabs(disty/ybs);
        QImage* tmp = removeY(b,nbrPix);
        if(bchanged == true){
            delete b;
        }
        b = tmp;
        bchanged = true;
    }
    else{
        int nbrPix = qFabs(disty/yas);
        QImage* tmp = removeY(a,nbrPix);
        if(achanged == true){
            delete a;
        }
        a = tmp;
        achanged = true;
    }
    distx = (a->width()*xas) - (b->width()*xbs);
    disty = (a->height()*yas) - (b->height()*ybs);
    if(distx <0){
        int nbrPix = qFabs(distx/xbs);
        QImage* tmp = removeXL(b,nbrPix);
        if(bchanged == true){
            delete b;
        }
        b = tmp;
        bchanged = true;
    }
    else{
        int nbrPix = qFabs(distx/xas);
        QImage* tmp = removeX(a,nbrPix);
        if(achanged == true){
            delete a;
        }
        a = tmp;
        achanged = true;
    }
    if(disty < 0){
        int nbrPix = qFabs(disty/ybs);
        QImage* tmp = removeYL(b,nbrPix);
        if(bchanged == true){
            delete b;
        }
        b = tmp;
        bchanged = true;
    }
    else{
        int nbrPix = qFabs(disty/yas);
        QImage* tmp = removeYL(a,nbrPix);
        if(achanged == true){
            delete a;
        }
        a = tmp;
        achanged = true;
    }


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
    //qDebug() << "taille f";
    //qDebug() <<a->width() << " " << a->height();
    //qDebug() <<b->width() << " " << b->height();
    QVector<QImage*> res;
    res.append(a);
    res.append(b);
    return res;
}
QImage* SerieDamier::removeX(QImage* a, int nbrX){
    QImage*c = new QImage(a->width()-nbrX,a->height(),QImage::Format_Grayscale16);
    for(int y=0;y<a->height();y++){
        for(int x=nbrX;x<a->width();x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x-nbrX,y,color);
        }
    }
    return c;

}
QImage* SerieDamier::removeY(QImage* a, int nbrY){
    QImage*c = new QImage(a->width(),a->height()-nbrY,QImage::Format_Grayscale16);
    for(int y=nbrY;y<a->height();y++){
        for(int x=0;x<a->width();x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x,y-nbrY,color);
        }
    }
    return c;

}
QImage* SerieDamier::removeYL(QImage* a, int nbrY){
    QImage*c = new QImage(a->width(),a->height()-nbrY,QImage::Format_Grayscale16);
    for(int y=0;y<a->height()-nbrY;y++){
        for(int x=0;x<a->width();x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x,y,color);
        }
    }
    return c;

}
QImage* SerieDamier::removeXL(QImage* a, int nbrX){
    QImage*c = new QImage(a->width()-nbrX,a->height(),QImage::Format_Grayscale16);
    for(int y=0;y<a->height();y++){
        for(int x=0;x<a->width()-nbrX;x++){
            QColor color = a->pixelColor(x,y);
            c->setPixelColor(x,y,color);
        }
    }
    return c;

}
void SerieDamier::InitialisationImages(){
    int t =1;
    m_liste = QVector<QImage*>();
    if(m_synchro == NULL){
        m_synchro = new synchro(m_s1,m_s2);
    }

    QProgressDialog progress("Fusion des Images","Annuler",0,m_synchro->getMax(),m_parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    for(int i=0;i<m_synchro->getMax()-1;i++){
       int* tab = m_synchro->getIndex(i);
       //qDebug() << tab[0] <<"/"<<m_s1->getMax()-1<< " " << tab[1] << "/"<<m_s2->getMax()-1;
       QVector<QImage*> res = rescale(m_s1->getIndex(tab[0]),m_s2->getIndex(tab[1]),m_s1->getIdI(tab[0])->getX(),
               m_s1->getIdI(tab[0])->getY(),m_s1->getIdI(tab[0])->getXPix(),m_s1->getIdI(tab[0])->getYPix(),
               m_s2->getIdI(tab[1])->getX(),m_s2->getIdI(tab[1])->getY(),m_s2->getIdI(tab[1])->getXPix(),
               m_s2->getIdI(tab[1])->getYPix());
       m_liste.append(damier(res.at(0),res.at(1)));
       progress.setValue(t);
       t++;
    }
}
QImage* SerieDamier::getIndex(int i){
    return m_liste.at(i);
}
int SerieDamier::getMax(){
    return m_liste.size();
}
QHash<QString,QString> SerieDamier::parms(){
    QHash<QString,QString> map;
    map.insert("dx",QString::number(m_dX));
    map.insert("dy",QString::number(m_dY));
    return map;
}
void SerieDamier::Updateparams(QHash<QString, QString> params){
    QHash<QString, QString>::iterator i = params.find("dx");
    while (i != params.end() && i.key() == "dx") {
       m_dX = i.value().toDouble();
        ++i;
    }
    i = params.find("dy");
    while (i != params.end() && i.key() == "dy") {
       m_dY = i.value().toInt();
        ++i;
    }
}
