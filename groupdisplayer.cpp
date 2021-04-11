#include "groupdisplayer.h"

GroupDisplayer::GroupDisplayer(QWidget *parent) : QFrame(parent)
{
    m_s1 = new serieDisplayer(this);
    m_s2 = new serieDisplayer(this);
    super = parent;
}

void GroupDisplayer::afficherSerie(Series* sr){
    if(m_s1->isEmpty()){
        m_s1->linkSerie(sr);
        m_s1->generateImages();
        emit loadSerie(m_s1,0);
    }
    else if(m_s2->isEmpty()){
        m_s2->linkSerie(sr);
        m_s2->generateImages();
        emit loadSerie(m_s2,1);
    }

}
void GroupDisplayer::fusionnerSerie(){
    SerieFusion* sF = new SerieFusion(super);
    sF->ajouter(m_s1->getSerie());
    sF->ajouter(m_s2->getSerie());
    m_s1->linkSerie(sF);
    m_s1->generateImages();
    emit loadSerie(m_s1,2);
}
void GroupDisplayer::addLayout(QHBoxLayout *layout){
    layout->addWidget(m_s1);
    layout->addWidget(m_s2);
}
void GroupDisplayer::setW(int w){
    m_s1->changerS(w/2);
    m_s2->changerS(w/2);
    update();
}
