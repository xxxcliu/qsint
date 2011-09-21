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


void DocumentViewController::onDocumentsChanged()
{
}


void DocumentViewController::onDocumentCreated(Document* doc)
{
    QWidget* view = doc->view();
    Q_ASSERT(view != NULL);

    addTab(view, doc->name());
}


}

