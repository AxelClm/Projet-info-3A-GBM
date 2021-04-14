#ifndef IMAGEDISPLAYER_H
#define IMAGEDISPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QtDebug>
class ImageDisplayer : public QWidget
{
    Q_OBJECT
public:
    ImageDisplayer(QWidget *parent);
    virtual ~ImageDisplayer();
    void linkImage(QImage* image);
    void changerS(int width);

private:
    QImage* m_image;
protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // IMAGEDISPLAYER_H
