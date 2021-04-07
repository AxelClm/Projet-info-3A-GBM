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
#include "series.h"
#include "seriedisplayer.h"
#include "seriefusion.h"
class Fenetre : public QWidget
{
    Q_OBJECT
private:
    DicomReader m_dcm;
    serieDisplayer* m_sDM;
    serieDisplayer* m_sDM2;
    //serieDisplayer* m_sD2;
    QFrame* m_FrameG;
    int m_GWidth;
    QHBoxLayout* m_HBLayout;
    QHBoxLayout* m_HBMidLayout;
    QVBoxLayout* m_VBDroiteLayout;
    QVBoxLayout* m_VBGaucheLayout;
    QPushButton* m_ajoutSerie;
    QPushButton* m_fusionSerie;
    serieDisplayer* m_sd;
    SerieFusion* m_fusion;
    void resizeEvent(QResizeEvent* event);
public:
    Fenetre();
    virtual ~Fenetre();
public slots:
    void ajouterSerie();
    void afficherSerie(Series* sr);

};
#endif // FENETRE_H
