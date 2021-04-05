#include "dicomreader.h"

DicomReader::DicomReader()
{

}
dicomImage DicomReader::parseDicom(QString chemin){
    m_dcmimg = dicomImage();
    QFile fichier(chemin);
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
    }
    return m_dcmimg;
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
