#ifndef VIEWCONTROLER_H
#define VIEWCONTROLER_H

#include <QTabWidget>
#include <QVector>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <seriedisplayer.h>
#include <QPushButton>
#include <QHash>
#include <QSpinBox>
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
    QVector<QLabel*> m_ptsLabel1;
    QVector<QSpinBox*> m_spinB1;
    QVector<QPushButton*> m_button1;
    QLabel* m_opa;
    QSlider* m_opaS;
    QPushButton* m_opaB;
    QHash<QString,QString> generateParamsFusion();
    QHash<QString,QString> generateParamsBase();
    serieDisplayer** m_STab;

public slots:
    void linkSerieDisplayer(serieDisplayer* sd, int num);
    void fastParamsFusion();
    void bigParamsFusion();
    void fastParamsSer();
    void bigParamsSet();
signals:
    void fastUpdate(QHash<QString,QString>,int);
    void bigUpdate(QHash<QString,QString>);
};

#endif // VIEWCONTROLER_H
