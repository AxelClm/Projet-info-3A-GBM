#ifndef DICOMIMAGE_H
#define DICOMIMAGE_H
#include "dicomrow.h"
#include <QByteArray>
#include <QBitArray>
#include <QVector>
#include <QImage>
#include <QtMath>
#include <iostream>
#include "iostream"
class dicomImage
{
public:
    dicomImage();
    void ajouterRow(QByteArray Tag, QByteArray VR,QByteArray data,QByteArray size);
    bool generateImage();
    QImage* getImage();
    double getSliceL();
private:
    QVector<DicomRow> m_header;
    QImage* m_image;
    int m_Row;
    int m_Columns;
    int m_BitAllocated;
    int m_BitStored;
    int m_Indeximage;
    double m_sliceL;
    QByteArray LireRow(QByteArray::iterator* i,int rows);
    QByteArray reverse(QByteArray* a);

};

#endif // DICOMIMAGE_H
