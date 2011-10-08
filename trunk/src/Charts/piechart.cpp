#include <math.h>

#include "piechart.h"


namespace QSint
{


PieChart::PieChart(QWidget *parent) :
    PlotterBase(parent)
{
    m_index = 0;
}


void PieChart::setActiveIndex(int index)
{
    m_index = 0;

    update();

    if (!m_model)
        return;

    if (index >= 0 && index < m_model->rowCount())
        m_index = index;
}


void PieChart::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    drawBackground(p);

    drawContent(p);
}


void PieChart::drawContent(QPainter &p)
{
    int margin = 3;

    int w = width()-margin*2;
    int h = height()-margin*2;

    int w2 = w / 2;
    int h2 = h / 2;

    QRect pieRect = QRect(margin, margin, w, h);

    p.translate(pieRect.x(), pieRect.y());
    p.drawEllipse(0, 0, w, h);

    if (!m_model)
        return;

    int row_count = m_model->rowCount();
    if (!row_count)
        return;

    int count = m_model->columnCount();
    if (!count)
        return;

    if (m_index < 0 || m_index >= count)
        m_index = 0;

    int c = m_index;

    double totalValue = 0;
    for (int r = 0; r < row_count; r++)
    {
        const QModelIndex index(m_model->index(r, c));
        double value = m_model->data(index).toDouble();

        if (value > 0.0)
            totalValue += value;
    }

    double startAngle = 0.0;

    for (int r = 0; r < row_count; r++)
    {
        const QModelIndex index(m_model->index(r, c));
        double value = m_model->data(index).toDouble();

        if (value > 0.0) {
            double angle = 360*value/totalValue;

            QPen pen(qvariant_cast<QColor>(m_model->headerData(r, Qt::Vertical, Qt::ForegroundRole)));
            p.setPen(pen);

            QBrush brush(qvariant_cast<QBrush>(m_model->headerData(r, Qt::Vertical, Qt::BackgroundRole)));
            p.setBrush(brush);

            p.drawPie(0, 0, w, h, int(startAngle*16), int(angle*16));

            startAngle += angle;
        }
    }
}


}
