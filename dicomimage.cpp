#include "dicomimage.h"

dicomImage::dicomImage()
{
    //On initialise l'image (On part du principe qu'il n'y aura jamais de probleme pr lire les dicoms
    //En effet , je n'ai pas la prétention de faire un lecteurs de dicom universel mais qui fonctionne au moins
    //Avec mon set de dicom).
    m_BitAllocated = -1;
    m_BitStored = -1;
    m_Indeximage = -1;
    m_Row = -1;
    m_Columns = -1;
}
void dicomImage::ajouterRow(QByteArray Tag, QByteArray VR, QByteArray data, QByteArray size){
    DicomRow a = DicomRow(Tag,VR,data,size);
    m_header.append(a);
    if (Tag.toHex() == "e07f1000"){
        m_Indeximage = m_header.size()-1; // On part du principe que le programme n'aura jamais de threads...
    }
    else if (Tag.toHex() == "28000001"){
        bool ok;
        m_BitAllocated = data.toHex().toInt(&ok,16);
        //qDebug() << "m_BitAllocated :" << m_BitAllocated;
    }
    else if (Tag.toHex() == "28000101"){
        bool ok;
        m_BitStored = data.toHex().toInt(&ok,16);
        //qDebug() << "m_BitStored :" << m_BitStored;
    }
    else if (Tag.toHex() == "28001000"){
        bool ok;
        m_Row = data.toHex().toInt(&ok,16);
        //qDebug() << "m_Row :" <<m_Row ;
    }
    else if (Tag.toHex() == "28001100"){
        bool ok;
        m_Columns = data.toHex().toInt(&ok,16);
        //qDebug() << "m_Row :" <<m_Row ;
    }
    else if (Tag.toHex() == "20004110"){
        bool ok;
        m_sliceL = reverse(&data).toDouble(&ok);
        qDebug() << m_sliceL;
    }
}
bool dicomImage::generateImage(){
    if(m_BitAllocated == -1 || m_BitStored == -1 || m_Indeximage ==-1 || m_Row == -1 || m_Columns == -1){
        return false;
    }
    int max = 0;
    QByteArray data = m_header[m_Indeximage].getData(); 
    QByteArray::iterator z = data.begin();
    m_image = new QImage(m_Row,m_Columns,QImage::Format_Grayscale16);
    for(int m=0;m<m_Columns;m++){
        for(int n=0;n<m_Row;n++){
            QByteArray tmp = LireRow(&z,2);
            tmp = reverse(&tmp);
            QBitArray tmpBit(m_BitAllocated,false);
            for(int i = 0; i < tmp.count(); ++i) {
              if((i+1)*8 > m_BitAllocated){
                  for(int b = 0; b < 8 - m_BitAllocated%8; b++) {
                    tmpBit.setBit( i * 8 + b, tmp.at(i) & (1 << (7 - b)) );
                  }
              }
              else{
                  for(int b = 0; b < 8; b++) {
                    tmpBit.setBit( i * 8 + b, tmp.at(i) & (1 << (7 - b)) );
                  }
              }
            }
            // On met maintenant les bits en Int
            int a = 0;
            for(int i =0 ; i < m_BitStored ; i++){
                bool b = tmpBit.at(m_BitAllocated-i-1);

                if(b == true){
                    a = a + qPow(2,i);
                }
            }
            QColor color;
            if(a>max){
                max = a;
            }
            int intensite = 255*a/qPow(2,m_BitStored);
            color.setBlue(intensite);
            color.setRed(intensite);
            color.setGreen(intensite);
            m_image->setPixelColor(n,m,color);
        }
    }
    //qDebug() << "Max Image : " << max;
    return true;
}
QByteArray dicomImage::LireRow(QByteArray::iterator* i , int rows){
    QByteArray res;
    for(int m = 0; m<rows; m++){
       res.append(**i);
        ++(*i);
    }
    return res;
}
QByteArray dicomImage::reverse(QByteArray *a){
    QByteArray res;
    QByteArray::reverse_iterator i;
    i = a->rbegin();
    while(i != a->rend()){
        res.append(*i);
        i++;
    }
    return res;
}
QImage* dicomImage::getImage(){
    return m_image;
}
double dicomImage::getSliceL(){
    return m_sliceL;
}
