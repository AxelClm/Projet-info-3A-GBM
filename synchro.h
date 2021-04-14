#ifndef SYNCHRO_H
#define SYNCHRO_H
#include "series.h"
#include <vector>
class synchro
{
public:
    synchro(Series* a,Series* b);
    ~synchro();
    int getMax();
    int* getIndex(int i);
private:
    void synchroniseSeries(Series*a,Series*b);
    QVector<int*> m_liste;
};

#endif // SYNCHRO_H
