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
    virtual ~dicomImage();
    void ajouterRow(QByteArray Tag, QByteArray VR,QByteArray data,QByteArray size);
    bool generateImage(int bruit);
    QImage* getImage();
    double getSliceL();
    double getX();
    double getY();
    double getXPix();
    double getYPix();
    int getBruit();
    void setBruit(int val);
    private:
    QVector<DicomRow> m_header;
    QImage* m_image;
    int m_Row;
    int m_Columns;
    int m_BitAllocated;
    int m_BitStored;
    int m_Indeximage;
    int m_MaxPix;
    double m_x;
    double m_y;
    double m_xPix;
    double m_yPix;
    double m_sliceL;
    QByteArray LireRow(QByteArray::iterator* i,int rows);
    QByteArray reverse(QByteArray* a);

};

#endif // DICOMIMAGE_H
