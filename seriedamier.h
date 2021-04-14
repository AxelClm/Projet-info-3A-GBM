#ifndef SERIEDAMIER_H
#define SERIEDAMIER_H

#include "series.h"
#include "synchro.h"
class SerieDamier : public Series
{
public:
    SerieDamier(QWidget* parent);
    ~SerieDamier();
    void ajouter(Series*s);
    QImage* fastRender(int i) override;
    void InitialisationImages() override;
    QImage* getIndex(int i) override;
    int getMax() override;
    QHash<QString,QString> parms() override;
    void Updateparams(QHash<QString,QString> params)override;
private:
    QWidget* m_parent;
    QImage* damier(QImage* a, QImage* b);
    QVector<QImage*> m_liste;
    QVector<QImage*> rescale(QImage*a,QImage*b,double xa , double ya, double xas , double yas , double xb, double yb,double xbs, double ybs);
    QImage* removeX(QImage*a,int nbrX);
    QImage* removeY(QImage*a,int nbrY);
    QImage* removeXL(QImage*a,int nbrX);
    QImage* removeYL(QImage*a,int nbrY);
    int m_dX;
    int m_dY;
    Series*m_s1;
    Series* m_s2;
    synchro* m_synchro;
};

#endif // SERIEDAMIER_H
