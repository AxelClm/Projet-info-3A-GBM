#ifndef SERIES_H
#define SERIES_H
#include <dicomimage.h>
#include <vector>
#include <QProgressDialog>
#include <QHash>
#include <QThreadPool>
#include <parsingjob.h>
#include <QMutex>
class Series: public QObject
{
    Q_OBJECT
public:
    Series(QWidget* a);
    void ajouter(dicomImage* dcm);
    virtual QImage* fastRender(int i);
    virtual void InitialisationImages();
    //virtual void getCurrent();
    virtual QImage* getIndex(int i);
    dicomImage* getIdI(int i);
    virtual int getMax();
    virtual QHash<QString,QString> parms();
    virtual void Updateparams(QHash<QString,QString> params);
private:
    QWidget* m_parent;
    bool m_generated;
    QVector<dicomImage*> m_liste;
};

#endif // SERIES_H
