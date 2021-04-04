#ifndef DICOMIMAGE_H
#define DICOMIMAGE_H
#include "dicomrow.h"
#include <QVector>
#include <QImage>
class dicomImage
{
public:
    dicomImage();
    void ajouterRow(QByteArray Tag, QByteArray VR,QByteArray data,QByteArray size);
private:
    QVector<DicomRow> m_header;
    QImage m_image;
};

#endif // DICOMIMAGE_H
