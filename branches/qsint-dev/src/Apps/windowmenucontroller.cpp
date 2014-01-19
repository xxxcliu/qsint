#include "windowmenucontroller.h"
#include "documentaction.h"


namespace QSint
{


WindowMenuController::WindowMenuController(ParentClass* parent) :
    BaseClass(tr("&Window"), parent)
{
    m_actionCloseAll = new QAction(tr("Close all windows"), this);
}


void WindowMenuController::onShowRootMenu(QMenu* menu)
{
    m_actionCloseAll->setEnabled(!m_windowActions.isEmpty());

    ADD_ACTION(menu, m_actionCloseAll);

    ADD_SEPARATOR(menu);

    Document* currentDoc = activeDocument();
    foreach(DocumentAction* action, m_windowActions)
    {
        action->setChecked(action->document() == currentDoc);

        ADD_ACTION(menu, action);
    }
}


// Actions and events

void WindowMenuController::connectActions()
{
    BaseClass::connectActions();

    if (documentController())
    {
        connect(documentController(), SIGNAL(documentCreated(Document*)),
                this, SLOT(updateActions(Document*)));

        connect(documentController(), SIGNAL(documentChanged(Document*)),
                this, SLOT(updateActions(Document*)));
    }

    if (documentViewController())
    {
        connect(documentViewController(), SIGNAL(documentActivated(Document*)),
                this, SLOT(updateActions(Document*)));
    }
}


void WindowMenuController::updateActions(Document*)
{
    qDeleteAll(m_windowActions);
    m_windowActions.clear();

    if (documentController())
    {
        const QList<Document*>& docs = documentController()->documents();

        foreach(Document* doc, docs)
        {
            m_windowActions.append(new DocumentAction(doc));
        }
    }
}


void WindowMenuController::onMenuTriggered(QAction* action)
{
    DocumentAction* act = dynamic_cast<DocumentAction*>(action);
    if (act == NULL)
        return;

    if (documentViewController())
    {
        documentViewController()->setActiveDocument(act->document());
    }
}


}
