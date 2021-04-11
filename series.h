#ifndef SERIES_H
#define SERIES_H
#include <dicomimage.h>
#include <vector>
#include <QProgressDialog>
class Series
{
public:
    Series(QWidget* a);
    void ajouter(dicomImage* dcm);
    virtual QImage* getFirst();
    virtual void InitialisationImages();
    //virtual void getCurrent();
    virtual QImage* getIndex(int i);
    virtual int getMax();
private:
    QWidget* m_parent;
    bool m_generated;
    QVector<dicomImage*> m_liste;
};

#endif // SERIES_H
