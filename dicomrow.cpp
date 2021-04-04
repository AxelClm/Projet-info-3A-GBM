#include "dicomrow.h"

DicomRow::DicomRow(QByteArray Tag, QByteArray VR, QByteArray data,QByteArray size){
    m_Tag = Tag;
    m_VR = VR;
    m_data = data;
    m_size = size;
}
