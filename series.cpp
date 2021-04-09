#include "series.h"

Series::Series()
{
    imgGenerer = false;
}
void Series::ajouter(dicomImage* dcm){
    imgGenerer = false;
    m_liste.append(dcm);
}
QImage* Series::getFirst(){
    m_liste.at(0)->generateImage();
    return m_liste.at(0)->getImage();
}
void Series::InitialisationImages(){
    int i =1;
    QVector<dicomImage*>::iterator it;
    for(it = m_liste.begin();it<m_liste.end();it++){
        //It.hasNext() ne marche pas (boucle while) ???
        (*it)->generateImage();
        qDebug() << i <<"/"<<m_liste.size();
        i++;
    }

}

