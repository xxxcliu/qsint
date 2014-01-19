#ifndef MENUACTIONCONTROLLER_H
#define MENUACTIONCONTROLLER_H


#include <QMenu>

#include "actioncontroller.h"


namespace QSint
{


class MenuActionController : public ActionController
{
    Q_OBJECT

    typedef ActionController BaseClass;
    typedef MainWindow ParentClass;

public:
    explicit MenuActionController(const QString& name, ParentClass *parent);

    // menu methods
    virtual QMenu* createMenu();
    virtual QMenu* rootMenu()
            { return m_menu; }

protected Q_SLOTS:
    virtual void onMenuTriggered(QAction*)
            {}

protected:
    QMenu* m_menu;
    QString m_name;
};


}

#endif // MENUACTIONCONTROLLER_H
