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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QCoreApplication>
class Fenetre : public QWidget
{
    Q_OBJECT
private:
    DicomReader m_dcm;
    ImageDisplayer* m_imgD;
    QHBoxLayout* m_HBLayout;
    QHBoxLayout* m_HBMidLayout;
    QVBoxLayout* m_VBDroiteLayout;
    QVBoxLayout* m_VBGaucheLayout;
    QPushButton* m_ajoutSerie;
    QPushButton* m_fusionSerie;
    void resizeEvent(QResizeEvent* event);
public:
    Fenetre();
    virtual ~Fenetre();

};
#endif // FENETRE_H
