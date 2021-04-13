#ifndef PARSINGJOB_H
#define PARSINGJOB_H

#include <QRunnable>
#include <dicomimage.h>
#include <QProgressDialog>
#include <QMutex>
class ParsingJob :public QObject, public QRunnable
{
    Q_OBJECT
public:
    ParsingJob();
    void linkDicomImage(dicomImage*dcm);
    void linkProgress(int * i, QProgressDialog* progress,QMutex* mutex);
private:
    dicomImage* m_dcm;
    QProgressDialog* m_p;
    int* m_i;
    QMutex* m_mutex;
    void run();
signals:
    void terminer(int);
};

#endif // PARSINGJOB_H
