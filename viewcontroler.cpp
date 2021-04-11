#include "viewcontroler.h"

ViewControler::ViewControler(QWidget * parent) : QTabWidget(parent)
{
    createPage("Série 1",0);
    createPage("Série 2",1);
    createPage("Fusion",2);
    this->removeTab(2);
    this->removeTab(1);
    this->removeTab(0);
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
    if(index == 2){
        m_opa = new QLabel(m_Page.at(2));
        m_opa->setText("Opacité :");
        m_opaS = new QSlider(Qt::Horizontal,m_Page.at(2));
        m_opaB = new QPushButton(m_Page.at(2));
        m_opaB->setText("Appliquer à toute la série");
        m_opaS->setMaximum(1000);
        m_Layout.at(index)->addWidget(m_opa);
        m_Layout.at(index)->addWidget(m_opaS);
        m_Layout.at(index)->addWidget(m_opaB);
        QObject::connect(m_opaS,SIGNAL(valueChanged(int)),this,SLOT(fastParamsFusion()));
        QObject::connect(m_opaB,SIGNAL(clicked()),this,SLOT(bigParamsFusion()));
    }
    this->addTab(m_Page.at(index),nom);

}
void ViewControler::linkSerieDisplayer(serieDisplayer* sd, int num){
    switch (num) {
        case 0:{
           this->insertTab(0,m_Page.at(0),"Image 1");
           m_Slider.at(num)->setMaximum(sd->getSerie()->getMax());
           QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
           break;
        }
        case 1:{
           this->insertTab(1,m_Page.at(1),"Image 2");
           m_Slider.at(num)->setMaximum(sd->getSerie()->getMax());
           QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
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
          QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
          QObject::connect(this,SIGNAL(fastUpdate(QHash<QString,QString>,int)),sd,SLOT(changeParam(QHash<QString,QString>,int)));
          QObject::connect(this,SIGNAL(bigUpdate(QHash<QString,QString>)),sd,SLOT(changeParamAll(QHash<QString,QString>)));
        }
    }
}
void ViewControler::fastParamsFusion(){
    emit fastUpdate(generateParamsFusion(),m_Slider.at(2)->value());
}
QHash<QString,QString> ViewControler::generateParamsFusion(){
    double val = double(m_opaS->value())/1000;
    QHash<QString,QString> map;
    map.insert("opa",QString::number(val));
    return map;
}
void ViewControler::bigParamsFusion(){
    emit bigUpdate(generateParamsFusion());
}
