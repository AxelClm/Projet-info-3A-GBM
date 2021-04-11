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
    DicomReader();
    dicomImage* parseDicom(QString chemin);
private:
    dicomImage* m_dcmimg;
    void LireTagSuivant(QByteArray::iterator* i,bool tagR);
    QByteArray LireRow(QByteArray::iterator* i,int rows);
    QByteArray reverse(QByteArray* a);
    void LireItemSuivantSQ(QByteArray::iterator*i);
};

#endif // DICOMREADER_H
