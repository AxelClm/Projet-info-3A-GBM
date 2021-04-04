#ifndef DICOMROW_H
#define DICOMROW_H

#include <QByteArray>
#include <QtDebug>
class DicomRow
{
public:
    DicomRow(QByteArray Tag,QByteArray VR,QByteArray data,QByteArray size);
private:
    QByteArray m_Tag;
    QByteArray m_VR;
    QByteArray m_data;
    QByteArray m_size;

};

#endif // DICOMROW_H
