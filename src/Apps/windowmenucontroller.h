#ifndef WINDOWMENUCONTROLLER_H
#define WINDOWMENUCONTROLLER_H


#include "actioncontroller.h"


namespace QSint
{


class WindowMenuController : public ActionController
{
    typedef ActionController BaseClass;
    typedef MainWindow ParentClass;

    Q_OBJECT
public:
    explicit WindowMenuController(ParentClass *parent);

    // menu methods
    virtual QMenu* createMenu();
    virtual QMenu* rootMenu() { return m_menuWindow; }

protected:
    virtual void onShowRootMenu(QMenu* menu);

    QMenu* m_menuWindow;
};


}


#endif // WINDOWMENUCONTROLLER_H
