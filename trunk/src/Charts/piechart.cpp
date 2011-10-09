#include <math.h>

#include "piechart.h"


namespace QSint
{


PieChart::PieChart(QWidget *parent) :
    PlotterBase(parent)
{
    m_index = 0;

    m_margin = 3;
}


void PieChart::setActiveIndex(int index)
{
    if (m_index == index)
        return;

    m_index = 0;

    scheduleUpdate();

    if (!m_model)
        return;

    if (index >= 0 && index < m_model->rowCount())
        m_index = index;
}


void PieChart::paintEvent(QPaintEvent *)
{
    if (m_buffer.size() != size() || m_repaint)
    {
        m_buffer = QPixmap(size());
        m_repaint = false;

        QPainter p2(&m_buffer);
        p2.setRenderHint(QPainter::Antialiasing);

        drawBackground(p2);

        drawContent(p2);
    }

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.drawPixmap(0, 0, m_buffer);

    drawHighlight(p);
}


void PieChart::drawContent(QPainter &p)
{
    int w = width() - m_margin*2;
    int h = height() - m_margin*2;

    int w2 = w / 2;
    int h2 = h / 2;

    QRect pieRect = QRect(m_margin, m_margin, w, h);

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
        return;

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


void PieChart::drawHighlight(QPainter &p)
{
    if (m_mousePos.isNull())
        return;

    if (!m_model)
        return;

    int row_count = m_model->rowCount();
    if (!row_count)
        return;

    int count = m_model->columnCount();
    if (!count)
        return;

    if (m_index < 0 || m_index >= count)
        return;

    int w = width() - m_margin*2;
    int h = height() - m_margin*2;

    int w2 = w / 2;
    int h2 = h / 2;

    QRect pieRect = QRect(m_margin, m_margin, w, h);

    // check if we're inside piechart at all
    if (!pieRect.contains(m_mousePos))
        return;

    // Determine the distance from the center point of the pie chart.
    double cx = m_mousePos.x() - w2;
    double cy = h2 - m_mousePos.y();
    double d = pow(pow(cx, 2) + pow(cy, 2), 0.5);
    if (d == 0)
        return;

    // Determine the angle of the point.
    double mouseAngle = (180 / M_PI) * acos(cx/d);
    if (cy < 0)
        mouseAngle = 360 - mouseAngle;

    qDebug() << mouseAngle;

    // Find the corresponding data segment
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

            if (startAngle <= mouseAngle && mouseAngle <= (startAngle + angle))
            {
                // highlight the segment and break
                p.translate(pieRect.x(), pieRect.y());

                QPen pen(qvariant_cast<QColor>(m_model->headerData(r, Qt::Vertical, Qt::ForegroundRole)));
                p.setPen(pen);

                QBrush brush(QBrush(Qt::black, Qt::Dense5Pattern));
                p.setBrush(brush);

                //p.setOpacity(0.2);

                p.drawPie(0, 0, w, h, int(startAngle*16), int(angle*16));

                break;
            }

            startAngle += angle;
        }
    }

}


}
