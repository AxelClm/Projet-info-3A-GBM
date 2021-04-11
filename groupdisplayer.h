#ifndef GROUPDISPLAYER_H
#define GROUPDISPLAYER_H

#include <QFrame>
#include <QWidget>
#include <QHBoxLayout>
#include "seriedisplayer.h"
#include "seriefusion.h"
class GroupDisplayer : public QFrame
{
    Q_OBJECT
public:
    GroupDisplayer(QWidget* parent);
    void addLayout(QHBoxLayout* layout);
    void setW(int w);
private:
    serieDisplayer* m_s1;
    serieDisplayer* m_s2;
    QWidget* super;
public slots:
    void afficherSerie(Series* sr);
    void fusionnerSerie();
};

#endif // GROUPDISPLAYER_H
