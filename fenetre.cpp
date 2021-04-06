#include "fenetre.h"

Fenetre::Fenetre(){
    m_VBGaucheLayout = new QVBoxLayout();
    m_HBMidLayout = new QHBoxLayout();
    m_VBDroiteLayout = new QVBoxLayout();
    m_HBLayout = new QHBoxLayout();
    m_HBLayout->addLayout(m_VBGaucheLayout);
    m_HBLayout->addLayout(m_HBMidLayout);
    m_HBLayout->addLayout(m_VBDroiteLayout);
    this->setLayout(m_HBLayout);
    //Creation menu gauche
    m_VBGaucheLayout->setAlignment(Qt::AlignTop);
    m_ajoutSerie = new QPushButton(this);
    m_ajoutSerie->setText("Ajout Serie");
    m_VBGaucheLayout->addWidget(m_ajoutSerie);
    m_fusionSerie = new QPushButton(this);
    m_fusionSerie->setText("Fusion Serie");
    m_VBGaucheLayout->addWidget(m_fusionSerie);
    m_VBGaucheLayout->setContentsMargins(0,10,0,10);
    //Creation menu millieu (tmp)
    m_imgD = new ImageDisplayer(this);
    m_HBMidLayout->addWidget(m_imgD);
    dicomImage a = m_dcm.parseDicom("C:/1-110.dcm");
    a.generateImage();
    m_imgD->linkImage(a.getImage());
    //Creation menu gauche
    this->setGeometry(0,0,900,600);
    QSize NSize = QSize(850,600);
    QSize OSize = QSize(this->size());
    QResizeEvent * ev = new  QResizeEvent(NSize,OSize);
    QCoreApplication::postEvent(this,ev);
}

Fenetre::~Fenetre()
{
}
void Fenetre::resizeEvent(QResizeEvent* event){
    int mGRatio = 20;
    int mGWidth = event->size().width()*mGRatio/100;
    if (mGWidth > 150){
        mGWidth = 150;
    }
    qDebug() << mGWidth;
    m_ajoutSerie->resize(mGWidth,m_ajoutSerie->height());
    m_fusionSerie->resize(mGWidth,m_fusionSerie->height());
    m_ajoutSerie->setContentsMargins(0,10,0,10);
    m_fusionSerie->setContentsMargins(0,10,0,10);
    QWidget::resizeEvent(event);

}


