#include "multipagewidget.h"

#include <QDebug>


namespace QSint
{


MultiPageWidget::MultiPageWidget(QWidget *parent) :
    QWidget(parent)
{
    m_pageStack = new QStackedWidget(this);
    m_pageStack->setFrameStyle(QFrame::StyledPanel);

    m_layout = new QGridLayout(this);
    m_layout->addWidget(m_pageStack, 1, 1);
    m_layout->setSpacing(0);

    m_buttonGroup.setExclusive(true);

    m_pageArea[PP_TOP].setup(PP_TOP, Qt::AlignLeft);
    m_pageArea[PP_BOTTOM].setup(PP_BOTTOM, Qt::AlignLeft);
    m_pageArea[PP_LEFT].setup(PP_LEFT, Qt::AlignRight | Qt::AlignTop);
    m_pageArea[PP_RIGHT].setup(PP_RIGHT, Qt::AlignLeft | Qt::AlignTop);

    connect(&m_buttonGroup, SIGNAL(buttonClicked(int)), m_pageStack, SLOT(setCurrentIndex(int)));
}


int MultiPageWidget::addPage(QWidget *page, const QString &label, PagePosition position)
{
    return checkAndAddPage(page, QIcon(), label, position, INT_MAX, 0);
}


int MultiPageWidget::addPage(QWidget *page, const QIcon &icon, const QString &label, PagePosition position)
{
    return checkAndAddPage(page, icon, label, position, INT_MAX, 0);
}


int MultiPageWidget::insertPage(QWidget *page, const QString &label, PagePosition position, int index, int layer)
{
    return checkAndAddPage(page, QIcon(), label, position, index, layer);
}


int MultiPageWidget::insertPage(QWidget *page, const QIcon &icon, const QString &label, PagePosition position, int index, int layer)
{
    return checkAndAddPage(page, icon, label, position, index, layer);
}


void MultiPageWidget::setAlignment(Qt::Alignment align, PagePosition position)
{
    m_pageArea[position].setAlignment(align);
}


Qt::Alignment MultiPageWidget::alignment(PagePosition position) const
{
    return m_pageArea[position].alignment();
}


int MultiPageWidget::checkAndAddPage(QWidget *page, const QIcon &icon, const QString &label, PagePosition position, int index, int layer)
{
    int pageIndex = m_pageStack->indexOf(page);
    if (pageIndex >= 0)
        return -1;  // cannot add: already added

    pageIndex = m_pageStack->addWidget(page);

    PageAreaInfo &areaInfo = m_pageArea[position];
    areaInfo.createIfNeeded(this, m_layout);

    QAbstractButton *button = areaInfo.insertButton(icon, label, index, layer);

    m_buttonGroup.addButton(button, pageIndex);

    // activate the tab
    button->setChecked(true);
    m_pageStack->setCurrentIndex(pageIndex);

    return pageIndex;
}


// PageAreaInfo

MultiPageWidget::PageAreaInfo::PageAreaInfo():
    m_areaWidget(NULL)
{
}


void MultiPageWidget::PageAreaInfo::setup(MultiPageWidget::PagePosition position, Qt::Alignment alignment)
{
    m_position = position;
    m_alignment = alignment;
}


void MultiPageWidget::PageAreaInfo::createIfNeeded(QWidget *parent, QGridLayout *grid)
{
    if (m_areaWidget == NULL)
    {
        m_areaWidget = new QWidget(parent);

        switch (m_position)
        {
            case PP_BOTTOM:
                grid->addWidget(m_areaWidget, 2, 1);
                m_areaWidget->setLayout(m_areaLayout = new QHBoxLayout());
                break;
            case PP_LEFT:
                grid->addWidget(m_areaWidget, 1, 0);
                m_areaWidget->setLayout(m_areaLayout = new QVBoxLayout());
                break;
            case PP_RIGHT:
                grid->addWidget(m_areaWidget, 1, 2);
                m_areaWidget->setLayout(m_areaLayout = new QVBoxLayout());
                break;
            default: //case PP_TOP:
                grid->addWidget(m_areaWidget, 0, 1);
                m_areaWidget->setLayout(m_areaLayout = new QHBoxLayout());
                break;
        }

        m_areaLayout->setSpacing(0);
        m_areaLayout->setContentsMargins(0,0,0,0);

        m_areaLayout->addStretch();
        m_spacer1 = m_areaLayout->itemAt(0)->spacerItem();

        isVertical() ? m_buttonsLayout = new QHBoxLayout() : m_buttonsLayout = new QVBoxLayout();
        m_buttonsLayout->setSpacing(0);
        m_buttonsLayout->setContentsMargins(0,0,0,0);
        m_areaLayout->addLayout(m_buttonsLayout);

        m_areaLayout->addStretch();
        m_spacer2 = m_areaLayout->itemAt(2)->spacerItem();       
    }

    setAlignment(m_alignment);
}


void MultiPageWidget::PageAreaInfo::setAlignment(Qt::Alignment align)
{
    m_alignment = align;

    bool isSpacer1, isSpacer2;

    if (isVertical())
    {
        isSpacer1 = m_alignment & (Qt::AlignBottom | Qt::AlignVCenter);
        isSpacer2 = m_alignment & (Qt::AlignTop | Qt::AlignVCenter);

        m_spacer1->changeSize(1, isSpacer1 ? 1 : 0, QSizePolicy::Ignored, isSpacer1 ? QSizePolicy::MinimumExpanding : QSizePolicy::Fixed);
        m_spacer2->changeSize(1, isSpacer2 ? 1 : 0, QSizePolicy::Ignored, isSpacer2 ? QSizePolicy::MinimumExpanding : QSizePolicy::Fixed);
    }
    else
    {
        isSpacer1 = m_alignment & (Qt::AlignRight | Qt::AlignHCenter);
        isSpacer2 = m_alignment & (Qt::AlignLeft | Qt::AlignHCenter);

        m_spacer1->changeSize(isSpacer1 ? 1 : 0, 1, isSpacer1 ? QSizePolicy::MinimumExpanding : QSizePolicy::Fixed, QSizePolicy::Ignored);
        m_spacer2->changeSize(isSpacer2 ? 1 : 0, 1, isSpacer2 ? QSizePolicy::MinimumExpanding : QSizePolicy::Fixed, QSizePolicy::Ignored);
    }

    m_spacer1->invalidate();
    m_spacer2->invalidate();
    m_areaLayout->invalidate();
}


QAbstractButton* MultiPageWidget::PageAreaInfo::insertButton(const QIcon &icon, const QString &label, int index, int row)
{
    QPushButton *button = new QPushButton(icon, label, m_areaWidget);
    button->setCheckable(true);

    QBoxLayout *rowLayout = NULL;
    if (row < 0)
    {
        m_rowLayouts.prepend(rowLayout = createRowLayout());
    }
    else if (row >= m_rowLayouts.count())
    {
        m_rowLayouts.append(rowLayout = createRowLayout());
    }
    else
    {
        rowLayout = m_rowLayouts.at(row);
    }

    rowLayout->insertWidget(index, button);

    return button;
}


QBoxLayout* MultiPageWidget::PageAreaInfo::createRowLayout()
{
    QBoxLayout *rowLayout;
    if (isVertical())
    {
        rowLayout = new QVBoxLayout();
        rowLayout->setAlignment(Qt::AlignTop);
    }
    else
        rowLayout = new QHBoxLayout();

    rowLayout->setSpacing(0);
    rowLayout->setContentsMargins(0,0,0,0);

    m_buttonsLayout->addLayout(rowLayout);

    return rowLayout;
}


} // namespace

