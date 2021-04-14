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
#include <QFileDialog>
#include <QDirIterator>
#include <QFrame>
#include <QSlider>
#include "series.h"
#include "seriedisplayer.h"
#include "seriefusion.h"
#include "seriedamier.h"
#include "groupdisplayer.h"
#include "viewcontroler.h"
class Fenetre : public QWidget
{
    Q_OBJECT
private:
    DicomReader m_dcm;
    ViewControler* m_tab;
    //serieDisplayer* m_sD2;
    QFrame* m_FrameG;
    QFrame* m_FrameD;
    GroupDisplayer* m_GD;
    int m_GWidth;
    QHBoxLayout* m_HBLayout;
    QHBoxLayout* m_HBMidLayout;
    QVBoxLayout* m_VBDroiteLayout;
    QVBoxLayout* m_VBGaucheLayout;
    QSlider* m_slider;
    QPushButton* m_ajoutSerie;
    QPushButton* m_fusionSerie;
    QPushButton* m_damierSerie;
    serieDisplayer* m_sd;
    SerieFusion* m_fusion;
    void resizeEvent(QResizeEvent* event);
public:
    Fenetre();
    virtual ~Fenetre();
public slots:
    void ajouterSerie();

};
#endif // FENETRE_H
