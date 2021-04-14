#include "seriefusion.h"

SerieFusion::SerieFusion(QWidget* parent) : Series(parent)
{
    m_parent = parent;
    m_s1 = NULL;
    m_s2 = NULL;
    m_ratio = 0.5;
    m_pt1 = 85;
    m_pt2 = 170;
    m_synchro = NULL;
}
SerieFusion::~SerieFusion(){
    delete m_synchro; // On ne supprime pas les autres pointeurs car les adresses serviront tj
}
void SerieFusion::ajouter(Series* s){
    if(m_s1 == NULL){
        m_s1 = s;
    }
    else if(m_s2 == NULL){
        m_s2 =s;
    }
}
QImage* SerieFusion::fastRender(int index){
    if(m_synchro == NULL){
        m_synchro = new synchro(m_s1,m_s2);
    }
    int* tab = m_synchro->getIndex(index);
    QVector<QImage*> res = rescale(m_s1->getIndex(tab[0]),m_s2->getIndex(tab[1]),m_s1->getIdI(tab[0])->getX(),
            m_s1->getIdI(tab[0])->getY(),m_s1->getIdI(tab[0])->getXPix(),m_s1->getIdI(tab[0])->getYPix(),
            m_s2->getIdI(tab[1])->getX(),m_s2->getIdI(tab[1])->getY(),m_s2->getIdI(tab[1])->getXPix(),
            m_s2->getIdI(tab[1])->getYPix());
    return fusion(res.at(0),res.at(1));
}

QImage* SerieFusion::fusion(QImage*a,QImage*b){
    QImage* c = new QImage(a->width(),a->height(),QImage::Format_RGB16);
    for(int y = 0 ; y<a->height() ; y++){
        for(int x=0;x<a->width();x++){
            QColor pixa = a->pixelColor(x,y);
            QColor pixb = b->pixelColor(x,y);
            int moy = -pixb.black() + 255;
            int moy2 = -pixa.black() +255;
            QColor color;
            if(moy<m_pt1){ // Simple fonction affines pour donner un effet Noir ->Rouge -> jaune -> blanc
               int tmp = moy2*m_ratio +moy*(1-m_ratio)*(255/m_pt1);
               color.setGreen(moy2*m_ratio);
               color.setBlue(moy2*m_ratio);
               if(tmp > 255){
                   color.setRed(255);
               }
               else{
                   color.setRed(tmp);
               }
               c->setPixelColor(x,y,color);
            }
            else if(moy<m_pt2){
                int tmp = moy2*m_ratio +(moy*(255/(m_pt2-m_pt1))-(255/(m_pt2-m_pt1))*m_pt1)*(1-m_ratio);
                color.setRed(moy2*m_ratio+127*(1-m_ratio));
                color.setBlue(moy2*m_ratio);
                if(tmp > 255){
                    color.setGreen(255);
                }
                else{
                    color.setGreen(tmp);
                }
                c->setPixelColor(x,y,color);
            }
            else if (moy>m_pt2){
                int tmp = moy2*m_ratio +(moy*(255/(255-m_pt2))-(255/(255-m_pt2))*m_pt2)*(1-m_ratio);
                color.setRed(moy2*m_ratio+127*(1-m_ratio));
                color.setGreen(moy2*m_ratio+127*(1-m_ratio));
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

QVector<QImage*> SerieFusion::rescale(QImage*a,QImage*b,double xa , double ya, double xas , double yas , double xb, double yb,double xbs, double ybs){
    bool achanged = false;
    bool bchanged = false;
    //Meme code que pour damier
    qreal distx = qFabs(xa)-qFabs(xb);
    qreal disty = qFabs(ya)-qFabs(yb);

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
    m_liste = QVector<QImage*>();
    if(m_synchro == NULL){
        m_synchro = new synchro(m_s1,m_s2);
    }
    //qDebug()<< synch.getMax();
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
       m_liste.append(fusion(res.at(0),res.at(1)));
       progress.setValue(t);
       t++;
    }
    //qDebug() << "fini2";
}
QImage* SerieFusion::getIndex(int i){
    return m_liste.at(i);
}
int SerieFusion::getMax(){
    return m_liste.size();
}
QHash<QString,QString> SerieFusion::parms(){ //Obliger de prendre cette QHash pour garder la meme structure de code
    //Choix contestable
    QHash<QString,QString> map;
    map.insert("opa",QString::number(m_ratio));
    map.insert("pt1",QString::number(m_pt1));
    map.insert("pt2",QString::number(m_pt2));
    return map;
}
void SerieFusion::Updateparams(QHash<QString, QString> params){
    QHash<QString, QString>::iterator i = params.find("opa");
    while (i != params.end() && i.key() == "opa") {
       m_ratio = i.value().toDouble();
        ++i;
    }
    i = params.find("pt1");
    while (i != params.end() && i.key() == "pt1") {
       m_pt1 = i.value().toInt();
        ++i;
    }
    i = params.find("pt2");
    while (i != params.end() && i.key() == "pt2") {
       m_pt2 = i.value().toInt();
        ++i;
    }
}
