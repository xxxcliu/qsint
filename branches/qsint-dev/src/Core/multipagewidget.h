#ifndef MULTIPAGEWIDGET_H
#define MULTIPAGEWIDGET_H

#include <QtGui/QStackedWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QButtonGroup>


namespace QSint
{


class MultiPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MultiPageWidget(QWidget *parent = 0);

    enum PagePosition
    {
        PP_TOP = 0,
        PP_BOTTOM,
        PP_LEFT,
        PP_RIGHT,
        _PP_LAST_
    };

    int addPage(QWidget *page, const QString &label, PagePosition position = PP_TOP);
    int addPage(QWidget *page, const QIcon &icon, const QString &label, PagePosition position = PP_TOP);
    int insertPage(QWidget *page, const QString &label, PagePosition position = PP_TOP, int index = INT_MAX, int layer = 0);
    int insertPage(QWidget *page, const QIcon &icon, const QString &label, PagePosition position = PP_TOP, int index = INT_MAX, int layer = 0);

    void setAlignment(Qt::Alignment align, PagePosition position = PP_TOP);
    Qt::Alignment alignment(PagePosition position = PP_TOP) const;

protected:
    virtual int checkAndAddPage(QWidget *page, const QIcon &icon, const QString &label, PagePosition position, int index, int layer);

    QStackedWidget *m_pageStack;
    QGridLayout *m_layout;
    QButtonGroup m_buttonGroup;

    class PageAreaInfo
    {
    public:
        PageAreaInfo();

        void setup(PagePosition position, Qt::Alignment alignment);
        void createIfNeeded(QWidget *parent, QGridLayout *grid);

        void setAlignment(Qt::Alignment align);
        Qt::Alignment alignment() const
                { return m_alignment; }

        QAbstractButton* insertButton(const QIcon &icon, const QString &label, int index, int row);

        bool isVertical() const
                { return m_position == PP_LEFT || m_position == PP_RIGHT; }

    protected:
        QBoxLayout* createRowLayout();

        PagePosition m_position;
        Qt::Alignment m_alignment;

        QWidget *m_areaWidget;
        QBoxLayout *m_areaLayout;

        QSpacerItem *m_spacer1, *m_spacer2;
        QBoxLayout *m_buttonsLayout;

        QList<QBoxLayout*> m_rowLayouts;
    };

    PageAreaInfo m_pageArea[_PP_LAST_];
};


} // namespace

#endif // MULTIPAGEWIDGET_H

