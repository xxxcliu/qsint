#ifndef PIECHART_H
#define PIECHART_H

#include <QtGui>

#include "plotterbase.h"


namespace QSint
{


class PieChart : public PlotterBase
{
    Q_OBJECT

public:
    PieChart(QWidget *parent = 0);

    void setActiveIndex(int index);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void drawContent(QPainter &p);
    virtual void drawHighlight(QPainter &p);

protected:
    int m_index;

    int m_margin;
};


}


#endif
