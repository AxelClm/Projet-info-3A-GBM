#ifndef SERIEFUSION_H
#define SERIEFUSION_H
#include "series.h"
#include <QColor>
#include "synchro.h"
class SerieFusion : public Series
{
public:
    SerieFusion(QWidget* parent);
    void ajouter(Series*);
    //void getCurrent();
    QImage* getFirst() override;
    void InitialisationImages() override;
    QImage* getIndex(int i) override;
    int getMax() override;
private:
    QWidget* m_parent;
    QImage* fusion(QImage* a, QImage* b);
    QVector<QImage*> m_liste;
    QVector<QImage*> rescale(QImage*a,QImage*b);
    QImage* removeX(QImage*a,int nbrX);
    QImage* removeY(QImage*a,int nbrY);
    QImage* removeXL(QImage*a,int nbrX);
    QImage* removeYL(QImage*a,int nbrY);
    Series*m_s1;
    Series* m_s2;

};

#endif // SERIEFUSION_H
