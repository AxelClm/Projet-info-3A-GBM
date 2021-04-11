#include "seriedisplayer.h"

serieDisplayer::serieDisplayer(QWidget *parent) : ImageDisplayer(parent)
{
    m_sr=NULL;
}
void serieDisplayer::linkSerie(Series* serie){
    m_sr = serie;
    linkImage(m_sr->fastRender(0));
}
void serieDisplayer::mouseReleaseEvent(QMouseEvent*){
    emit toucher(m_sr);
}
bool serieDisplayer::isEmpty(){
    if( m_sr ==NULL){
        return true;
    }
    else{
        return false;
    }
}
void serieDisplayer::generateImages(){
    if(m_sr !=NULL){
        m_sr->InitialisationImages();
    }
}
void serieDisplayer::changeImage(int i){
    if(!(i>m_sr->getMax()-1)){
        linkImage(m_sr->getIndex(i));
    }
}
void serieDisplayer::changeParam(QHash<QString,QString>params,int index){
    this->getSerie()->Updateparams(params);
    linkImage(this->getSerie()->fastRender(index));
}
void serieDisplayer::changeParamAll(QHash<QString,QString>params){
    this->getSerie()->Updateparams(params);
    this->generateImages();
}
Series* serieDisplayer::getSerie(){

    return m_sr;
}
