#include "viewcontroler.h"

ViewControler::ViewControler(QWidget * parent) : QTabWidget(parent)
{
    createPage("Série 1",0);
    createPage("Série 2",1);
    createPage("Fusion",2);
    createPage("Damier",3);
    this->removeTab(3);
    this->removeTab(2);
    this->removeTab(1);
    this->removeTab(0);
    this->m_STab = new serieDisplayer*[3];
}
ViewControler::~ViewControler(){
    m_Layout.clear();
    m_Page.clear();
    m_SliderLabel.clear();
    m_Slider.clear();
    m_ptsLabel1.clear();
    m_spinB1.clear();
    m_button1.clear();
    delete  m_opa;
    delete m_opaS;
    delete m_opaB;
    delete[] m_STab;
    delete m_LPt1;
    delete m_pt1;
    delete m_LPt2;
    delete m_pt2;
}
void ViewControler::createPage(QString nom,int index){
    m_Page.append(new QWidget());
    m_Layout.append(new QVBoxLayout());
    m_SliderLabel.append(new QLabel(m_Page.at(index)));
    m_SliderLabel.at(index)->setText("Progression :");
    m_Slider.append(new QSlider(Qt::Horizontal,m_Page.at(index)));
    m_Layout.at(index)->addWidget(m_SliderLabel.at(index));
    m_Layout.at(index)->addWidget(m_Slider.at(index));
    m_Layout.at(index)->setAlignment((Qt::AlignTop));
    m_Page.at(index)->setLayout(m_Layout.at(index));
    if(index < 2){
        m_ptsLabel1.append(new QLabel(m_Page.at(index)));
        m_ptsLabel1.at(index)->setText("bruit(px) :");
        m_spinB1.append(new QSpinBox(m_Page.at(index)));
        m_spinB1.at(index)->setMaximum(255);
        m_spinB1.at(index)->setMinimum(0);
        m_button1.append(new QPushButton(m_Page.at(index)));
        m_button1.at(index)->setText("Appliquer à toute la série");
        m_Layout.at(index)->addWidget(m_ptsLabel1.at(index));
        m_Layout.at(index)->addWidget(m_spinB1.at(index));
        m_Layout.at(index)->addWidget(m_button1.at(index));
        QObject::connect(m_spinB1.at(index),SIGNAL(valueChanged(int)),this,SLOT(fastParamsSer()));
        QObject::connect(m_button1.at(index),SIGNAL(clicked()),this,SLOT(bigParamsSet()));

    }
    if(index == 2){
        m_opa = new QLabel(m_Page.at(2));
        m_opa->setText("Opacité :");
        m_opaS = new QSlider(Qt::Horizontal,m_Page.at(2));
        m_opaB = new QPushButton(m_Page.at(2));
        m_opaB->setText("Appliquer à toute la série");
        m_opaS->setMaximum(1000);
        m_LPt1 = new QLabel(m_Page.at(2));
        m_LPt1->setText("Filtre: pt1");
        m_pt1 = new QSpinBox(m_Page.at(2));
        m_pt1->setMaximum(255);
        m_pt1->setMinimum(0);
        m_LPt2 = new QLabel(m_Page.at(2));
        m_LPt2->setText("Filtre: pt1");
        m_pt2 = new QSpinBox(m_Page.at(2));
        m_pt2->setMaximum(255);
        m_pt2->setMinimum(0);
        m_Layout.at(index)->addWidget(m_opa);
        m_Layout.at(index)->addWidget(m_opaS);
        m_Layout.at(index)->addWidget(m_LPt1);
        m_Layout.at(index)->addWidget(m_pt1);
        m_Layout.at(index)->addWidget(m_LPt2);
        m_Layout.at(index)->addWidget(m_pt2);
        m_Layout.at(index)->addWidget(m_opaB);
        QObject::connect(m_opaS,SIGNAL(valueChanged(int)),this,SLOT(fastParamsFusion()));
        QObject::connect(m_pt1,SIGNAL(valueChanged(int)),this,SLOT(fastParamsFusion()));
        QObject::connect(m_pt2,SIGNAL(valueChanged(int)),this,SLOT(fastParamsFusion()));
        QObject::connect(m_opaB,SIGNAL(clicked()),this,SLOT(bigParamsFusion()));
    }
    if(index == 3){
        m_ser = new QPushButton(m_Page.at(index));
        m_ser->setText("Appliquer à toute la série");
        m_LDx = new QLabel(m_Page.at(index));
        m_LDx->setText("Cadrillage : X");
        m_Dx = new QSpinBox(m_Page.at(index));
        m_Dx->setMinimum(2);
        m_LDy = new QLabel(m_Page.at(index));
        m_LDy->setText("Cadrillage : Y");
        m_pDy = new QSpinBox(m_Page.at(index));
        m_pDy->setMinimum(2);
        m_Layout.at(index)->addWidget(m_LDx);
        m_Layout.at(index)->addWidget(m_Dx);
        m_Layout.at(index)->addWidget(m_LDy);
        m_Layout.at(index)->addWidget(m_pDy);
        m_Layout.at(index)->addWidget(m_ser);
        QObject::connect(m_Dx,SIGNAL(valueChanged(int)),this,SLOT(fastParamsDamier()));
        QObject::connect(m_pDy,SIGNAL(valueChanged(int)),this,SLOT(fastParamsDamier()));
        QObject::connect(m_ser,SIGNAL(clicked()),this,SLOT(bigParamsDamier()));
    }
    m_remove.append(new QPushButton(m_Page.at(index)));
    m_remove.at(index)->setText("Enlever Serie");
    m_Layout.at(index)->addWidget(m_remove.at(index));
    QObject::connect(m_remove.at(index),SIGNAL(clicked()),this,SLOT(remove()));
    this->addTab(m_Page.at(index),nom);

}
void ViewControler::linkSerieDisplayer(serieDisplayer* sd, int num){
    switch (num) {
        case 0:{
           this->insertTab(0,m_Page.at(0),"Série 1");
           m_Slider.at(num)->setMaximum(sd->getSerie()->getMax());
           QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
           QHash<QString, QString> params = sd->getSerie()->parms();
           QHash<QString, QString>::iterator i = params.find("opa");
           int val = 0;
           while (i != params.end() && i.key() == "bruit") {
              val = i.value().toInt();
               ++i;
           }
           m_spinB1.at(num)->setValue(val);
           m_STab[num] = sd;
           break;
        }
        case 1:{
           this->insertTab(1,m_Page.at(1),"Série 2");
           m_Slider.at(num)->setMaximum(sd->getSerie()->getMax());
           QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
           QHash<QString, QString> params = sd->getSerie()->parms();
           QHash<QString, QString>::iterator i = params.find("opa");
           int val = 0;
           while (i != params.end() && i.key() == "bruit") {
              val = i.value().toInt();
               ++i;
           }
           m_spinB1.at(num)->setValue(val);
           m_STab[num] = sd;
           break;
        }
        case 2:{
          this->removeTab(0);
          this->insertTab(0,m_Page.at(2),"fusion");
          m_Slider.at(num)->setMaximum(sd->getSerie()->getMax());
          QHash<QString, QString> params = sd->getSerie()->parms();
          QHash<QString, QString>::iterator i = params.find("opa");
          double val = 0;
          while (i != params.end() && i.key() == "opa") {
             val = i.value().toDouble();
              ++i;
          }
          m_opaS->setValue(val*1000);
          i = params.find("pt1");
          while (i != params.end() && i.key() == "pt1") {
             m_pt1->setValue(i.value().toInt());
              ++i;
          }
          i = params.find("pt2");
          while (i != params.end() && i.key() == "pt2") {
             m_pt2->setValue(i.value().toInt());
              ++i;
          }
          QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
          m_STab[0] = sd;
          break;
        }
        case 3:{
         this->removeTab(0);
         this->insertTab(0,m_Page.at(3),"damier");
         m_Slider.at(3)->setMaximum(sd->getSerie()->getMax());
         QObject::connect(m_Slider.at(3),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
         QHash<QString, QString> params = sd->getSerie()->parms();
         QHash<QString, QString>::iterator i = params.find("dx");
         while (i != params.end() && i.key() == "dx") {
            m_Dx->setValue(i.value().toDouble());
             ++i;
         }
         i = params.find("dy");
         while (i != params.end() && i.key() == "dx") {
            m_pDy->setValue(i.value().toDouble());
            ++i;
         }
         break;
        }
    }
}
void ViewControler::unlinkSerie(int index){
    removeTab(index);
}
void ViewControler::fastParamsFusion(){
    QObject::connect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::connect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
    emit fastUpdate(generateParamsFusion(),m_Slider.at(2)->value());
    QObject::disconnect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::disconnect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));

}
QHash<QString,QString> ViewControler::generateParamsFusion(){
    double val = double(m_opaS->value())/1000;
    QHash<QString,QString> map;
    map.insert("opa",QString::number(val));
    map.insert("pt1",QString::number(m_pt1->value()));
    map.insert("pt2",QString::number(m_pt2->value()));
    return map;
}
void ViewControler::bigParamsFusion(){
    QObject::connect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::connect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
    emit bigUpdate(generateParamsFusion());
    QObject::disconnect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::disconnect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
}
void ViewControler::fastParamsSer(){
    QObject::connect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::connect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
    emit fastUpdate(generateParamsBase(),m_Slider.at(currentIndex())->value());
    // On part du principe qu'on peut pas modifier un tab pas visible
    QObject::disconnect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::disconnect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
}
void ViewControler::bigParamsSet(){
    QObject::connect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::connect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
    emit bigUpdate(generateParamsBase());
    QObject::disconnect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::disconnect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
}
QHash<QString,QString> ViewControler::generateParamsBase(){
    int val = m_spinB1.at(currentIndex())->value();
    QHash<QString,QString> map;
    map.insert("bruit",QString::number(val));
    return map;
}
void ViewControler::fastParamsDamier(){
    QObject::connect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::connect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
    emit fastUpdate(generateParamsDamier(),m_Slider.at(currentIndex())->value());
    QObject::disconnect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::disconnect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));

}
QHash<QString,QString> ViewControler::generateParamsDamier(){
    QHash<QString,QString> map;
    map.insert("dx",QString::number(m_Dx->value()));
    map.insert("dy",QString::number(m_pDy->value()));
    return map;
}
void ViewControler::bigParamsDamier(){
    QObject::connect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::connect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
    emit bigUpdate(generateParamsFusion());
    QObject::disconnect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),m_STab[currentIndex()],SLOT(changeParam(QHash<QString,QString>,int)));
    QObject::disconnect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),m_STab[currentIndex()],SLOT(changeParamAll(QHash<QString,QString>)));
}
void ViewControler::remove(){
    emit removed(this->currentIndex());
    this->setTabVisible(this->currentIndex(),false);
}
