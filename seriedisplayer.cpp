#include "seriedisplayer.h"

serieDisplayer::serieDisplayer(QWidget *parent) : ImageDisplayer(parent)
{
    m_sr=NULL;
}
void serieDisplayer::linkSerie(Series* serie){
    m_sr = serie;
    linkImage(m_sr->getFirst());
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