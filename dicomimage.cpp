#include "dicomimage.h"

dicomImage::dicomImage()
{

}
void dicomImage::ajouterRow(QByteArray Tag, QByteArray VR, QByteArray data, QByteArray size){
    DicomRow a = DicomRow(Tag,VR,data,size);
    m_header.append(a);
    if (Tag.toHex() == "e07f1000"){
        qDebug() << "imagePix";
    }
    else if (Tag.toHex() == "28000001"){
        bool ok;
        qDebug() <<"Bit Allocated :"<<data.toHex().toInt(&ok,16);
    }
    else if (Tag.toHex() == "28000101"){
        bool ok;
        qDebug() <<"Bit Stored :"<<data.toHex().toInt(&ok,16);
    }
    else if (Tag.toHex() == "28001000"){
        bool ok;
        qDebug() <<"Row :"<<data.toHex().toInt(&ok,16);
    }
    else if (Tag.toHex() == "28001100"){
        bool ok;
        qDebug() <<"Columns :"<<data.toHex().toInt(&ok,16);
    }
}
