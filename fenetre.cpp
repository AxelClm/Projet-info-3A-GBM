#include "fenetre.h"

Fenetre::Fenetre(){
    m_imgD = new ImageDisplayer(this);
    this->setFixedSize(512,512);
    dicomImage a = m_dcm.parseDicom("C:/1-089.dcm");
    a.generateImage();
    m_imgD->linkImage(a.getImage());
    update();
}

Fenetre::~Fenetre()
{
}


