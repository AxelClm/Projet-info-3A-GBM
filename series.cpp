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

