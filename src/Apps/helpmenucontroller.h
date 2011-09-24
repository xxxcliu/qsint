#ifndef HELPMENUCONTROLLER_H
#define HELPMENUCONTROLLER_H


#include "menuactioncontroller.h"


namespace QSint
{


class HelpMenuController : public MenuActionController
{
    typedef MenuActionController BaseClass;
    typedef MainWindow ParentClass;

public:
    explicit HelpMenuController(ParentClass *parent);

protected:
    virtual void onShowRootMenu(QMenu* menu);

    QAction* m_actionAbout;
};


}


#endif // HELPMENUCONTROLLER_H
