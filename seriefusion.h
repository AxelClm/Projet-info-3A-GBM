#ifndef SERIEFUSION_H
#define SERIEFUSION_H
#include "series.h"

class SerieFusion : public Series
{
public:
    SerieFusion();
    void ajouter(Series*);
    //void getCurrent();
    QImage* getFirst() override;
private:

};

#endif // SERIEFUSION_H
