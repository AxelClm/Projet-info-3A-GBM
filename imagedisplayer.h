#ifndef IMAGEDISPLAYER_H
#define IMAGEDISPLAYER_H

#include <QWidget>
#include <QImage>
#include <QPainter>
class ImageDisplayer : public QWidget
{
    Q_OBJECT
public:
    ImageDisplayer(QWidget *parent);
    void linkImage(QImage image);

private:
    QImage m_image;
protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // IMAGEDISPLAYER_H
