#include "viewcontroler.h"

ViewControler::ViewControler(QWidget * parent) : QTabWidget(parent)
{
    createPage("Série 1",0);
    createPage("Série 2",1);
    createPage("Fusion",2);
    this->removeTab(2);
    this->removeTab(1);
    this->removeTab(0);
    this->m_STab = new serieDisplayer*[3];
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
          QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
          m_STab[0] = sd;
          break;
        }
    }
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
