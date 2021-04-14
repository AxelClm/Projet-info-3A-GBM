#include "dicomrow.h"

DicomRow::DicomRow(QByteArray Tag, QByteArray VR, QByteArray data,QByteArray size){
    m_Tag = Tag;
    m_VR = VR;
    m_data = data;
    m_size = size;
}
DicomRow::~DicomRow(){

}
QByteArray DicomRow::getData(){
    return m_data;
}
QByteArray DicomRow::getSize(){
    return m_size;
}
QByteArray DicomRow::getTag(){
    return m_Tag;
}
QByteArray DicomRow::getVR(){
    return m_VR;
}
