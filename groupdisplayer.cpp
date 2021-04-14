#include "groupdisplayer.h"

GroupDisplayer::GroupDisplayer(QWidget *parent) : QFrame(parent)
{
    m_s1 = new serieDisplayer(this);
    m_s2 = new serieDisplayer(this);
    super = parent;
}
GroupDisplayer::~GroupDisplayer(){
    delete m_s1;
    delete m_s2;
    //delete super; Mauvaise idée
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
    if(m_s1->getSerie() == NULL || m_s2->getSerie() == NULL){
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Veuillez importer deux séries !");
        messageBox.setFixedSize(500,200);
    }
    else {
        SerieFusion* sF = new SerieFusion(super);
        sF->ajouter(m_s1->getSerie());
        sF->ajouter(m_s2->getSerie());
        m_s1->linkSerie(sF);
        m_s1->generateImages();
        emit loadSerie(m_s1,2);
    }
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
void GroupDisplayer::unloadSerie(int index){
    if(index == 0){
        m_s1->linkImage(NULL);
        m_s1->linkSerie(NULL);
        update();
    }
    else{
        m_s2->linkImage(NULL);
        m_s2->linkSerie(NULL);
    }
}
