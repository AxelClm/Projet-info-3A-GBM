#ifndef SERIES_H
#define SERIES_H
#include <dicomimage.h>
#include <vector>
class Series
{
public:
    Series();
    void ajouter(dicomImage* dcm);
    virtual QImage* getFirst();
    virtual void InitialisationImages();
    //virtual void getCurrent();
    //virtual void getNext();
private:
    bool imgGenerer;
    QVector<dicomImage*> m_liste;
};

#endif // SERIES_H
