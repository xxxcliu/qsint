#include "windowmenucontroller.h"
#include "mainwindow.h"
#include "document.h"
#include "documentaction.h"
#include "documentcontroller.h"
#include "documentviewcontroller.h"


namespace QSint
{


WindowMenuController::WindowMenuController(ParentClass* parent) :
    BaseClass(tr("&Window"), parent)
{
    m_actionCloseAll = new QAction(tr("Close all windows"), this);
}


void WindowMenuController::onShowRootMenu(QMenu* menu)
{
    ADD_ACTION(menu, m_actionCloseAll);

    ADD_SEPARATOR(menu);

    DocumentViewController* documentViewCntr = mainWindow()->documentViewController();
    if (documentViewCntr != NULL)
    {
        Document* currentDoc = documentViewCntr->activeDocument();

        foreach(DocumentAction* action, m_windowActions)
        {
            action->setChecked(action->document() == currentDoc);

            ADD_ACTION(menu, action);
        }
    }
}


// Actions and events

void WindowMenuController::connectActions()
{
    BaseClass::connectActions();

    DocumentController* documentCntr = mainWindow()->documentController();
    if (documentCntr != NULL)
    {
        connect(documentCntr, SIGNAL(changed()), this, SLOT(updateActions()));
    }

    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(switchDocument(QAction*)));
}


void WindowMenuController::updateActions()
{
    qDeleteAll(m_windowActions);
    m_windowActions.clear();

    DocumentController* documentCntr = mainWindow()->documentController();
    if (documentCntr != NULL)
    {
        const QList<Document*>& docs = documentCntr->documents();
        m_actionCloseAll->setEnabled(!docs.isEmpty());

        foreach(Document* doc, docs)
        {
            m_windowActions.append(new DocumentAction(doc));
        }

    } else
    {
        m_actionCloseAll->setEnabled(false);
    }
}


void WindowMenuController::switchDocument(QAction* action)
{
    DocumentAction* act = dynamic_cast<DocumentAction*>(action);
    if (act == NULL)
        return;

    DocumentViewController* documentViewCntr = mainWindow()->documentViewController();
    if (documentViewCntr != NULL)
    {
        documentViewCntr->setActiveDocument(act->document());
    }
}


}
