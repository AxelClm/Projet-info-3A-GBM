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
dicomImage::~dicomImage(){
    delete m_image;
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
        //qDebug() << m_sliceL;
    }
    else if (Tag.toHex() == "20003200"){
        QString dt = reverse(&data);
        QStringList a = dt.split("\\");
        m_x = a[0].toDouble();
        m_y = a[1].toDouble();
        //qDebug() <<"x =" <<m_x;
        //qDebug() <<"y =" <<m_y;
    }
    else if (Tag.toHex() == "28003000"){
        QString dt = reverse(&data);
        QStringList a = dt.split("\\");
        m_xPix = a[0].toDouble();
        m_yPix = a[1].toDouble();
        //qDebug() <<"xP =" <<m_xPix;
        //qDebug() <<"yP =" <<m_yPix;
    }
    else if (Tag.toHex() == "28000701"){
        bool ok;
        m_MaxPix = data.toHex().toInt(&ok,16);
        //qDebug() << m_MaxPix;
    }
}
bool dicomImage::generateImage(int bruit){
    if(m_BitAllocated == -1 || m_BitStored == -1 || m_Indeximage ==-1 || m_Row == -1 || m_Columns == -1){
        return false;
    }
    QByteArray data = m_header[m_Indeximage].getData(); 
    m_image = new QImage(m_Row,m_Columns,QImage::Format_Grayscale16);
    QByteArray::iterator z = data.begin();
    int nbrPix = 0;
    QBitArray tmpBit(m_BitAllocated,false);
    int a=0;
    int maxPix = 255*m_MaxPix/qPow(2,m_BitStored); //Les bits utilisé peuvent être different de ceux stoqués.
    while(z !=data.end()){ // On utilise un iterateur pour parcourir la data dans l'optique d'etre le plus rapide possible.
           for(int b = 0; b < 8; b++) {
               tmpBit.setBit( 1 * 8 + b, *z & (1 << (7 - b)) );
           }
           z++;
           for(int b = 0; b < 8; b++) {
               tmpBit.setBit( 0 * 8 + b, *z & (1 << (7 - b)) );
           }
           z++;
           a=0;
           for(int i =0 ; i < m_BitStored ; i++){ //On peut maintenant transformer les bit en int
               if(tmpBit.at(m_BitAllocated-i-1)==true){
                   a = a + qPow(2,i);
                   }
           }
           QColor color;

            int intensite = 255*a/qPow(2,m_BitStored);

            double coef = 255/(maxPix-bruit); //Simple fonction affine
            double corr = -coef*bruit;
            if(intensite < bruit){
               intensite = 0;
            }
            else{
                intensite = intensite*coef+corr; // On met notre intensité sur 255 car cela est le plus facile
                //Pour l'integration dans QT (Par ex il ne gére pas les image de 12 bits.)
             }
             color.setBlue(intensite);
             color.setRed(intensite);
             color.setGreen(intensite);
             m_image->setPixelColor(nbrPix%m_Row,nbrPix/m_Row,color);
             nbrPix++;

    }
     // On met maintenant les bits en Int
    //qDebug() << "Max Image : " << max;
    return true;
}
QByteArray dicomImage::LireRow(QByteArray::iterator* i , int rows){
    QByteArray res;
    for(int m = 0; m<rows; m++){ // Un row = 16 bits
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
double dicomImage::getX(){
    return m_x;
}
double dicomImage::getY(){
    return m_y;
}
double dicomImage::getXPix(){
    return m_xPix;
}
double dicomImage::getYPix(){
    return m_yPix;
}
