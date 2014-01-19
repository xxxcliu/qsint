#ifndef WINDOWMENUCONTROLLER_H
#define WINDOWMENUCONTROLLER_H


#include "menuactioncontroller.h"


namespace QSint
{


class DocumentAction;


class WindowMenuController : public MenuActionController
{
    typedef MenuActionController BaseClass;
    typedef MainWindow ParentClass;

    Q_OBJECT
public:
    explicit WindowMenuController(ParentClass *parent);

    virtual void connectActions();

protected Q_SLOTS:
    virtual void updateActions(Document*);
    virtual void onMenuTriggered(QAction*);

protected:
    virtual void onShowRootMenu(QMenu* menu);

    QAction* m_actionCloseAll;

    QList<DocumentAction*> m_windowActions;
};


}


#endif // WINDOWMENUCONTROLLER_H
