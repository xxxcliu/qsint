#ifndef HELPMENUCONTROLLER_H
#define HELPMENUCONTROLLER_H


#include "actioncontroller.h"


namespace QSint
{


class HelpMenuController : public ActionController
{
    typedef ActionController BaseClass;
    typedef MainWindow ParentClass;

public:
    explicit HelpMenuController(ParentClass *parent);

    // menu methods
    virtual QMenu* createMenu();
    virtual QMenu* rootMenu() { return m_menuHelp; }

protected:
    virtual void onShowRootMenu(QMenu* menu);

    QMenu* m_menuHelp;

    QAction* m_actionAbout;
};


}


#endif // HELPMENUCONTROLLER_H
