#ifndef VIEWCONTROLER_H
#define VIEWCONTROLER_H

#include <QTabWidget>
#include <QVector>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <seriedisplayer.h>
class ViewControler : public QTabWidget
{
    Q_OBJECT
public:
    ViewControler(QWidget* parent);
    void createPage(QString nom, int index);
private:
    QVector<QVBoxLayout*> m_Layout;
    QVector<QWidget*> m_Page;
    QVector<QLabel*> m_SliderLabel;
    QVector<QSlider*> m_Slider;
public slots:
    void linkSerieDisplayer(serieDisplayer* sd, int num);
};

#endif // VIEWCONTROLER_H
