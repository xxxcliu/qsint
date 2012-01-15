#include "documentviewcontroller.h"
#include "document.h"

// QSint Core
#include "tablistmenu.h"

// Qt
#include <QToolButton>


namespace QSint
{


DocumentViewController::DocumentViewController(QWidget *parent) :
    QTabWidget(parent)
{
    // create TabListMenu
    TabListMenu *tabMenu = new TabListMenu(this);
    tabMenu->setTabs(this);

    // create corner button
    QToolButton *tbTabsDropList = new QToolButton(this);
    tbTabsDropList->setPopupMode(QToolButton::InstantPopup);
    setCornerWidget(tbTabsDropList);

    // assing tabMenu to the tbTabsDropList
    tbTabsDropList->setMenu(tabMenu);
}


// Serialization

bool DocumentViewController::store(QSettings& /*set*/)
{
    return true;
}


bool DocumentViewController::restore(QSettings& /*set*/)
{
    return true;
}


Document* DocumentViewController::activeDocument()
{
    if (count() == 0)
        return NULL;

    if (m_viewDocMap.contains(currentWidget()))
        return m_viewDocMap[currentWidget()];

    return NULL;
}


bool DocumentViewController::setActiveDocument(Document* doc)
{
    if (doc == NULL)
        return false;

    QMap<QWidget*, Document*>::const_iterator iter;
    for (iter = m_viewDocMap.constBegin(); iter != m_viewDocMap.end(); iter++)
    {
        if (iter.value() == doc)
        {
            setCurrentWidget(iter.key());
            return true;
        }
    }

    return false;
}


void DocumentViewController::onDocumentsChanged()
{
}


void DocumentViewController::onDocumentCreated(Document* doc)
{
    QWidget* view = doc->view();
    Q_ASSERT(view != NULL);

    int index = addTab(view, doc->name());

    setTabToolTip(index, doc->path());

    m_viewDocMap[view] = doc;
}


}

