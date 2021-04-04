#include "dicomreader.h"

DicomReader::DicomReader()
{
    m_fini = false;
    QFile fichier("C:/1-110.dcm");
    fichier.open(QIODevice::ReadOnly);
    QByteArray content = fichier.readAll();
    QByteArray::iterator i;
    i = content.begin();
    for(int x=0 ; x<50 ; x++){
        QByteArray a;
        for(int m = 0; m<4;i++){
            a = a + *i;
            m++;
        }
        if(a =="DICM"){
            //qDebug()<< "Fichier dicom";
            break;
        }
    }
    while(i != content.end()){
        LireTagSuivant(&i,false);
        //qDebug() << "----";
    }



}
void DicomReader::LireTagSuivant(QByteArray::iterator* i,bool tagR){
    QByteArray tag;
    if(tagR == false){
         tag = LireRow(i,4);
         //qDebug() << tag.toHex();
     }
     QByteArray vrName = LireRow(i,2);
     //qDebug() << "VrName : " << vrName;
     if (vrName == "OB" || vrName == "UN" || vrName == "OW"){
        //qDebug("OB Case");
        LireRow(i,2);
        QByteArray size = LireRow(i,4);
        bool ok;
        //qDebug() << size.toHex();
        size = reverse(&size);
        int nRow =  size.toHex().toInt(&ok,16);
        //qDebug() << nRow;
        QByteArray data = LireRow(i,nRow);
        m_dcmimg.ajouterRow(tag,vrName,data,size);
        if(vrName == "OW"){
            //qDebug() << "Afficher image";
                int max = 0;
                QByteArray::iterator z = data.begin();
                qDebug() << data.length();
                m_image = QImage(512,512,QImage::Format_Grayscale16);
                qDebug("passer");
                int bit = 16;
                int bitA = 12;
                for(int m=0;m<512;m++){
                    for(int n=0;n<512;n++){
                        QByteArray tmp = LireRow(&z,2);
                        tmp = reverse(&tmp);
                        QBitArray tmpBit(bit,false);
                        for(int i = 0; i < tmp.count(); ++i) {
                          if((i+1)*8 > bit){
                              for(int b = 0; b < 8 - bit%8; b++) {
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
                        for(int i =0 ; i < bitA ; i++){
                            bool b = tmpBit.at(bit-i-1);

                            if(b == true){
                                a = a + qPow(2,i);
                            }
                        }
                        QColor color;
                        if(a > max){
                            max = a;
                        }
                        int intensite = 255*a/qPow(2,bitA);
                        color.setBlue(intensite);
                        color.setRed(intensite);
                        color.setGreen(intensite);
                        m_image.setPixelColor(n,m,color);
                    }
                }
                qDebug() << max;
            }

     }
     else if (vrName == "SQ"){
        //qDebug("SQ Case");
        LireRow(i,2);
        QByteArray size = LireRow(i,4);
        //qDebug() << size;
        if(size == "\xFF\xFF\xFF\xFF"){
            //qDebug() << "infinite l case";
            while(true){
                QByteArray tag2 = LireRow(i,4);
                //qDebug() << tag2;
                QByteArray itemDelimiter;
                itemDelimiter = itemDelimiter + "\xFE\xFF";
                itemDelimiter.append('\x00');
                itemDelimiter = itemDelimiter + "\xE0";
                //qDebug() << tag2 << itemDelimiter;
                if(tag2 == itemDelimiter){
                    //qDebug() << "ITEM CASE";
                    LireItemSuivantSQ(i);
                }
                else if (tag2 == "\xFE\xFF\xDD\xE0"){
                    //qDebug() << "Fin de la sequence";
                    LireRow(i,4);
                    break;
                }
                else{

                }
            }
        }
     }
     else{
         QByteArray size = LireRow(i,2);
         bool ok;
         size = reverse(&size);
         //qDebug() << size;
         int nRow =  size.toHex().toInt(&ok,16);
         //qDebug() << nRow;
         QByteArray data = LireRow(i,nRow);
         //qDebug() << data;
         m_dcmimg.ajouterRow(tag,vrName,reverse(&data),size);

     }

}
void DicomReader::LireItemSuivantSQ(QByteArray::iterator* i){
     QByteArray size = LireRow(i,4);
     //qDebug() << size;
     if(size =="\xFF\xFF\xFF\xFF"){
         while(true){
             //qDebug() <<"--";
             QByteArray tag = LireRow(i,4);
             //qDebug() << tag.toHex();
             if(tag == "\xFE\xFF\x0D\xE0"){
                //qDebug() << "fin de l'item";
                LireRow(i,4);
                break;
             }
             else{
                LireTagSuivant(i,true);
                //qDebug() << "----";
             }
         }
     }
}
QByteArray DicomReader::LireRow(QByteArray::iterator* i , int rows){
    QByteArray res;
    for(int m = 0; m<rows; m++){
       res.append(**i);
        ++(*i);
    }
    return res;
}
QByteArray DicomReader::reverse(QByteArray *a){
    QByteArray res;
    QByteArray::reverse_iterator i;
    i = a->rbegin();
    while(i != a->rend()){
        res = res + *i;
        i++;
    }
    return res;
}
