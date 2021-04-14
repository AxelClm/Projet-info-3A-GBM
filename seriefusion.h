#ifndef SERIEFUSION_H
#define SERIEFUSION_H
#include "series.h"
#include <QColor>
#include "synchro.h"
class SerieFusion : public Series
{
public:
    SerieFusion(QWidget* parent);
    ~SerieFusion();
    void ajouter(Series*);
    //void getCurrent();
    QImage* fastRender(int i) override;
    void InitialisationImages() override;
    QImage* getIndex(int i) override;
    int getMax() override;
    QHash<QString,QString> parms() override;
    void Updateparams(QHash<QString,QString> params)override;
private:
    QWidget* m_parent;
    QImage* fusion(QImage* a, QImage* b);
    QVector<QImage*> m_liste;
    QVector<QImage*> rescale(QImage*a,QImage*b,double xa , double ya, double xas , double yas , double xb, double yb,double xbs, double ybs);
    QImage* removeX(QImage*a,int nbrX);
    QImage* removeY(QImage*a,int nbrY);
    QImage* removeXL(QImage*a,int nbrX);
    QImage* removeYL(QImage*a,int nbrY);
    double m_ratio;
    Series*m_s1;
    Series* m_s2;
    int m_pt1;
    int m_pt2;
    synchro* m_synchro;

};

#endif // SERIEFUSION_H
