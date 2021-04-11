#ifndef SERIEDISPLAYER_H
#define SERIEDISPLAYER_H

#include <QWidget>
#include <QImage>
#include <imagedisplayer.h>
#include "series.h"
class serieDisplayer : public ImageDisplayer
{
    Q_OBJECT
public:
    explicit serieDisplayer(QWidget *parent = nullptr);
    void linkSerie(Series *);
    bool isEmpty();
    void generateImages();
    Series* getSerie();
private:
    Series* m_sr;
protected:
    void mouseReleaseEvent(QMouseEvent*) override;
signals:
     void toucher(Series*);
public slots:
     void changeImage(int index);
};

#endif // SERIEDISPLAYER_H
