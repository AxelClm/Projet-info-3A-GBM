#include "fenetre.h"

Fenetre::Fenetre(){
    m_sd= NULL;
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
    m_FrameG= new QFrame(this);
    m_ajoutSerie = new QPushButton(m_FrameG);
    m_ajoutSerie->setText("Ajout Serie");
    m_VBGaucheLayout->addWidget(m_ajoutSerie);
    m_fusionSerie = new QPushButton(m_FrameG);
    m_fusionSerie->setText("Fusion Serie");
    m_VBGaucheLayout->addWidget(m_fusionSerie);
    m_VBGaucheLayout->setContentsMargins(0,10,0,10);
    m_FrameG->setMaximumHeight(999999);
    m_VBGaucheLayout->addWidget(m_FrameG);
    //Creation menu millieu (tmp)
    m_GD = new GroupDisplayer(this);
    m_GD->setMaximumHeight(999999);
    m_HBMidLayout->addWidget(m_GD);
    m_HBMidLayout->setAlignment(Qt::AlignCenter);
    m_GD->addLayout(m_HBMidLayout);
    //Creation menu droit
    m_tab = new ViewControler(this);
    m_VBDroiteLayout->addWidget(m_tab);
    m_VBDroiteLayout->setAlignment(Qt::AlignTop);
    this->setGeometry(0,0,900,600);
    QSize NSize = QSize(850,600);
    QSize OSize = QSize(this->size());
    QResizeEvent * ev = new  QResizeEvent(NSize,OSize);
    QCoreApplication::postEvent(this,ev);
    QObject::connect(m_ajoutSerie,SIGNAL(clicked()),this,SLOT(ajouterSerie()));
    QObject::connect(m_fusionSerie,SIGNAL(clicked()),m_GD,SLOT(fusionnerSerie()));
    QObject::connect(m_GD,SIGNAL(loadSerie(serieDisplayer*,int)),m_tab,SLOT(linkSerieDisplayer(serieDisplayer*,int)));
}

Fenetre::~Fenetre()
{
}
void Fenetre::resizeEvent(QResizeEvent* event){
    int mGRatio = 20;
    int test = event->size().width()*mGRatio/100;
    if (test > 150){
        m_GWidth = 150;
    }
    else if(test < 100){
        m_GWidth = 100;
    }
    int taille = (event->size().width()-m_GWidth-200);
    //qDebug() << mGWidth;
    m_FrameG->setFixedWidth(m_GWidth);
    m_tab->setFixedWidth(m_GWidth);
    m_GD->setW(taille);
    if(m_sd != NULL){
        m_sd->changerS(m_GWidth);
    }
    QWidget::resizeEvent(event);

}

void Fenetre::ajouterSerie(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    QDirIterator it(dir,{"*.dcm"}, QDir::Files);
        Series* s = new Series(this);
        while(it.hasNext()){
            s->ajouter(m_dcm.parseDicom(it.next()));
        }
        m_sd = new serieDisplayer(m_FrameG);
        m_sd->linkSerie(s);
        m_VBGaucheLayout->addWidget(m_sd);
        m_sd->changerS(m_GWidth);
        QObject::connect(m_sd,SIGNAL(toucher(Series*)),m_GD,SLOT(afficherSerie(Series*)));
}

