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
    ~ViewControler();
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
    QLabel* m_LPt1;
    QSpinBox* m_pt1;
    QLabel* m_LPt2;
    QSpinBox* m_pt2;
    QVector<QPushButton*> m_remove;

public slots:
    void linkSerieDisplayer(serieDisplayer* sd, int num);
    void fastParamsFusion();
    void bigParamsFusion();
    void fastParamsSer();
    void bigParamsSet();
    void unlinkSerie(int index);
    void remove();
signals:
    void fastUpdate(QHash<QString,QString>,int);
    void bigUpdate(QHash<QString,QString>);
    void removed(int index);
};

#endif // VIEWCONTROLER_H
