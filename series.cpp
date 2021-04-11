#include "series.h"

Series::Series(QWidget* a)
{
    m_parent = a;
    m_generated = false;
}
void Series::ajouter(dicomImage* dcm){
    if(m_generated == true){
        dcm->generateImage();
    }
    m_liste.append(dcm);
}
QImage* Series::getFirst(){
    m_liste.at(0)->generateImage();
    return m_liste.at(0)->getImage();
}
void Series::InitialisationImages(){
    int i =1;
    QProgressDialog progress("Generation des Images","Annuler",0,getMax(),m_parent);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    QVector<dicomImage*>::iterator it;
    for(it = m_liste.begin();it<m_liste.end();it++){
        //It.hasNext() ne marche pas (boucle while) ???
        (*it)->generateImage();
        progress.setValue(i);
        qDebug() << i <<"/"<<m_liste.size();
        i++;
    }
    m_generated = true;

}
QImage *Series::getIndex(int i){
    if(m_generated == true){
        return m_liste.at(i)->getImage();
    }
    else{
        return NULL;
    }
}
int Series::getMax(){
    return m_liste.size();
}
dicomImage* Series::getIdI(int i){
    return m_liste.at(i);
}
