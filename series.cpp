#include "series.h"

Series::Series(QWidget* a)
{
    m_parent = a;
    m_generated = false;
    this->m_bruit =0;
}
Series::~Series(){
    m_liste.clear(); // On part du principe que ça détruit vraiment les images;
}
void Series::ajouter(dicomImage* dcm){
    if(m_generated == true){
        dcm->generateImage(m_bruit);
    }
    m_liste.append(dcm);
}
QImage* Series::fastRender(int i){
    m_liste.at(i)->generateImage(m_bruit);
    return m_liste.at(i)->getImage();
}
void Series::InitialisationImages(){
    int i =1;
    QMutex mutex;
    QProgressDialog progress("Generation des Images","Annuler",0,getMax());
    //progress.setModal(true);
    //progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    QVector<dicomImage*>::iterator it;
    QThreadPool *threadPool = new QThreadPool();
    threadPool->setMaxThreadCount(QThread::idealThreadCount());
    QVector<ParsingJob*> pile;
    for(it = m_liste.begin();it<m_liste.end();it++){
        //It.hasNext() ne marche pas (boucle while) ???
        ParsingJob* pJob = new ParsingJob(); // On met des threads pour aller plus vite
        pile.append(pJob);
        pJob->linkDicomImage(*it,m_bruit);
        pJob->linkProgress(&i,&progress,&mutex);
        pJob->setAutoDelete(true);
        QObject::connect(pJob,SIGNAL(terminer(int)),&progress,SLOT(setValue(int)));
        threadPool->start(pJob);
    }
    progress.exec();
    threadPool->waitForDone();
    m_generated = true;

}
QImage *Series::getIndex(int i){
    if(m_generated == true){
        return m_liste.at(i)->getImage();
    }
    else{
        return NULL;
    }
}
int Series::getMax(){
    return m_liste.size();
}
dicomImage* Series::getIdI(int i){
    return m_liste.at(i);
}
QHash<QString,QString> Series::parms(){
    QHash<QString,QString> map;
    map.insert("bruit",QString::number(m_bruit));
    return map;
}
void Series::Updateparams(QHash<QString, QString> params){
    QHash<QString, QString>::iterator i = params.find("bruit");
    while (i != params.end() && i.key() == "bruit") {
       m_bruit = i.value().toDouble();
        ++i;
    }
}
