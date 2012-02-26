#ifndef PLOTTERBASE_H
#define PLOTTERBASE_H

#include <QtGui>


namespace QSint
{


class AxisBase;


class PlotterBase : public QWidget
{
    Q_OBJECT
public:
    explicit PlotterBase(QWidget *parent = 0);


    // general
    void setBorderPen(const QPen &pen);
    inline const QPen& borderPen() const { return m_pen; }

    void setBackground(const QBrush &brush);
    inline const QBrush& background() const { return m_bg; }

    // items
    void setFont(const QFont &font);
    inline const QFont& font() const { return m_font; }

    void setItemPen(const QPen &pen);
    inline const QPen& itemPen() const { return m_itemPen; }

    // highlight
    void setHighlightTextColor(const QColor &color);
    inline const QColor& highlightTextColor() const { return m_hlTextColor; }

    void setHighlightPen(const QPen &pen);
    inline const QPen& highlightPen() const { return m_hlPen; }

    void setHighlightBrush(const QBrush &brush);
    inline const QBrush& highlightBrush() const { return m_hlBrush; }

    void setHighlightAlpha(double alpha);
    inline double highlightAlpha() const { return m_hlAlpha; }

    // render hints
    inline void setAntiAliasing(bool set) { m_antiAliasing = set;}


    // axis
    inline AxisBase* axisX() const { return m_axisX; }
    inline AxisBase* axisY() const { return m_axisY; }


    // model
    void setModel(QAbstractItemModel *model);
    inline QAbstractItemModel* model() const { return m_model; }


    // returned values
    QRect dataRect() const;

    const QPoint& mousePos() const { return m_mousePos; }
    QPoint globalMousePos() const { return mapToGlobal(m_mousePos); }

    const QModelIndex& highlightedIndex() const { return m_indexUnderMouse; }

Q_SIGNALS:
    void entered(const QModelIndex& index);
    void pressed(const QModelIndex& index);
    void clicked(const QModelIndex& index);
    void doubleClicked(const QModelIndex& index);

protected Q_SLOTS:
    void scheduleUpdate();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void leaveEvent(QMouseEvent *event);

    virtual void paintEvent(QPaintEvent *event);

    virtual void drawBackground(QPainter &p);
    virtual void drawForeground(QPainter &p);
    virtual void drawAxis(QPainter &p);
    virtual void drawContent(QPainter &p) = 0;

    void setIndexUnderMouse(const QModelIndex& index);

    AxisBase *m_axisX;
    AxisBase *m_axisY;

    QAbstractItemModel *m_model;

    QBrush m_bg;
    QPen m_pen;

    QPen m_itemPen;
    QFont m_font;

    QColor m_hlTextColor;
    QPen m_hlPen;
    QBrush m_hlBrush;
    double m_hlAlpha;

    QPixmap m_buffer;
    bool m_repaint;
    bool m_antiAliasing;

    QPoint m_mousePos;
    QModelIndex m_indexUnderMouse;
    QModelIndex m_indexClick;
};


} // namespace

#endif // PLOTTERBASE_H
