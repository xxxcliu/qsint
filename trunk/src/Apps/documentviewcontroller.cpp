#include "documentviewcontroller.h"
#include "document.h"

// QSint Core
#include "tablistmenu.h"

// Qt
#include <QToolButton>


namespace QSint
{


DocumentViewController::DocumentViewController(QWidget *parent) :
    QTabWidget(parent),
    m_activateNewDocument(true)
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

    // signals & slots
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onCurrentTabChanged(int)));
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


// internal slots

void DocumentViewController::onCurrentTabChanged(int /*index*/)
{
    if (m_viewDocMap.contains(currentWidget()))
    {
        Document* doc = m_viewDocMap[currentWidget()];
        Q_ASSERT(doc != NULL);

        onCurrentDocumentChanged(doc);

        emit currentDocumentChanged(doc);
    }
}


// slots and methods to be reimplemeted

void DocumentViewController::onDocumentsChanged()
{
}


void DocumentViewController::onDocumentCreated(Document* doc)
{
    QWidget* view = doc->view();
    Q_ASSERT(view != NULL);

    m_viewDocMap[view] = doc;

    int index = addTab(view, doc->name());
    if (m_activateNewDocument)
        setCurrentIndex(index);

    setTabToolTip(index, doc->path());

    // the one and only
    if (count() == 1)
        onCurrentTabChanged(0);
}


void DocumentViewController::onDocumentChanged(Document* doc)
{
    Q_ASSERT(doc != NULL);

    int index = indexOf(doc->view());
    if (index < 0)
        return;

    setTabToolTip(index, doc->path());
    setTabText(index, doc->name());
}


void DocumentViewController::onDocumentContentChanged(Document* doc)
{

}


void DocumentViewController::onCurrentDocumentChanged(Document* doc)
{
    Q_ASSERT(doc != NULL);
}


}

