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

public Q_SLOTS:
    // sets active index to the given column
    void setActiveIndex(int index);
    // sets active index to the given column
    void setActiveIndex(const QModelIndex &index);

protected:
    virtual void drawContent(QPainter &p);

    virtual void drawSegment(QPainter &p, const QRect& pieRect,
                               const QModelIndex &index, double value,
                               double angle1, double angle2,
                               bool isHighlighted);
protected:
    int m_index;

    int m_margin;
};


}


#endif
