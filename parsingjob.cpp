#include "parsingjob.h"

ParsingJob::ParsingJob()
{
    m_dcm = NULL;
    m_i = NULL;
    m_p = NULL;
}

void ParsingJob::linkDicomImage(dicomImage * dcm, int bruit){
    this->m_dcm = dcm;
    this->m_bruit = bruit;
}
void ParsingJob::linkProgress(int *i, QProgressDialog *progress , QMutex* mutex){
    this->m_i = i;
    this->m_p = progress;
    this->m_mutex = mutex;
}
void ParsingJob::run(){
    if(m_dcm != NULL){
        m_dcm->generateImage(m_bruit);
    }
    if(m_i != NULL && m_p != NULL){
        //MUTEX !!!
        m_mutex->lock();
        emit terminer(*m_i);
        *m_i = *m_i + 1;
        m_mutex->unlock();
    }
}
