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
class Fenetre : public QWidget
{
    Q_OBJECT
private:
    DicomReader m_dcm;
    QImage m_imageCT;
    QImage m_imagePET;
    QImage m_imageFusion;
    ImageDisplayer* m_imgD;
public:
    Fenetre();
    virtual ~Fenetre();
protected:
    void paintEvent(QPaintEvent *event) override;

};
#endif // FENETRE_H
