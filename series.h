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
private:
    bool imgGenerer;
    QVector<dicomImage*> m_liste;
};

#endif // SERIES_H
