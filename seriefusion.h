#ifndef SERIEFUSION_H
#define SERIEFUSION_H
#include "series.h"
#include <QColor>
class SerieFusion : public Series
{
public:
    SerieFusion();
    void ajouter(Series*);
    //void getCurrent();
    QImage* getFirst() override;
private:
    QImage* fusion(QImage* a, QImage* b);
    Series*m_s1;
    Series* m_s2;

};

#endif // SERIEFUSION_H
