#ifndef DICOMREADER_H
#define DICOMREADER_H

#include <QFile>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QBitArray>
#include <QtMath>
#include "dicomimage.h"
class DicomReader
{
public:
    QImage m_image;
    DicomReader();
    void LireTagSuivant(QByteArray::iterator* i,bool tagR);
    QByteArray LireRow(QByteArray::iterator* i,int rows);
    QByteArray reverse(QByteArray* a);
    void LireItemSuivantSQ(QByteArray::iterator*i);
private:
    dicomImage m_dcmimg;
    bool m_fini;
};

#endif // DICOMREADER_H
