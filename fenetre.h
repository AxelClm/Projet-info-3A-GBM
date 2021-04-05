#ifndef FENETRE_H
#define FENETRE_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QSize>
#include <imagedisplayer.h>
#include <dicomreader.h>
#include <dicomimage.h>
class Fenetre : public QWidget
{
    Q_OBJECT
private:
    DicomReader m_dcm;
    ImageDisplayer* m_imgD;
public:
    Fenetre();
    virtual ~Fenetre();

};
#endif // FENETRE_H
