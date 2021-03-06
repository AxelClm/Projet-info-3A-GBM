#include "synchro.h"

synchro::synchro(Series* a,Series* b)
{
    synchroniseSeries(a,b);
}
synchro::~synchro(){
    m_liste.clear();
}
void synchro::synchroniseSeries(Series* a,Series* b){
    //On fait des paires d'images par rapport a la coupe
    // Aurait pu etre mieux fait mais la precision est suffisante
    int ia = 0;
    int ib = 0;
    while (true) {
        if(ia >= a->getMax()-1 || ib >= b->getMax()-1){
            break;
        }

        if(a->getIdI(ia)->getSliceL() == b->getIdI(ib)->getSliceL()){
            int* tmp = new int[2];
            tmp[0] = ia;
            tmp[1] = ib;
            //qDebug() << ia << " : " << ib;
            //qDebug() << a->getIdI(ia)->getSliceL() << " == " <<  b->getIdI(ib)->getSliceL();
            m_liste.append(tmp);
            ia++;
            ib++;
        }
        else if(a->getIdI(ia)->getSliceL() < b->getIdI(ib)->getSliceL()){
            int* tmp = new int[2];
            tmp[0] = ia;
            tmp[1] = ib;
            //qDebug() << ia << " : " << ib;
            //qDebug() << a->getIdI(ia)->getSliceL() << " > " <<  b->getIdI(ib)->getSliceL();
            m_liste.append(tmp);
            ib++;
        }
        else if (a->getIdI(ia)->getSliceL() > b->getIdI(ib)->getSliceL()){
            int* tmp = new int[2];
            tmp[0] = ia;
            tmp[1] = ib;
            //qDebug() << ia << " : " << ib;
            //qDebug() << a->getIdI(ia)->getSliceL() << " < " <<  b->getIdI(ib)->getSliceL();
            m_liste.append(tmp);
            ia++;
        }
    }
}
int synchro::getMax(){
    return m_liste.size();
}
int* synchro::getIndex(int i){
    return m_liste.at(i);
}
