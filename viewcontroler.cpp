#include "viewcontroler.h"

ViewControler::ViewControler(QWidget * parent) : QTabWidget(parent)
{
    createPage("Image 1",0);
    createPage("Image 2",1);
    //createPage("Global",2);
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
    this->addTab(m_Page.at(index),nom);

}
void ViewControler::linkSerieDisplayer(serieDisplayer* sd,int num){
    switch (num) {
        case 0:{
           m_Slider.at(num)->setMaximum(sd->getSerie()->getMax());
           QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
           break;
        }
        case 1:{
           m_Slider.at(num)->setMaximum(sd->getSerie()->getMax());
           QObject::connect(m_Slider.at(num),SIGNAL(valueChanged(int)),sd,SLOT(changeImage(int)));
           break;
        }
    }
}
