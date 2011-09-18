#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H


#include <QObject>

class QMenu;
class QToolBar;
class QAction;


namespace QSint
{


class MainWindow;


#define ADD_ACTION(target, action) \
        if (action != NULL) \
                target->addAction(action);

#define ADD_SEPARATOR(target) \
        target->addSeparator();


#define CONNECT_ACTION(action, controller, slot) \
    if (action != NULL) \
        connect(action, SIGNAL(triggered()), controller, SLOT(slot));


class ActionController : public QObject
{
    Q_OBJECT

    typedef MainWindow ParentClass;

public:
    explicit ActionController(ParentClass *parent);

    inline ParentClass* mainWindow()
            { return (ParentClass*)parent(); }

    // menu methods
    virtual QMenu* createMenu()
            { return NULL; }

    virtual QMenu* rootMenu()
            { return NULL; }

    // toolbar methods
    virtual QToolBar* createToolBar(Qt::ToolBarArea* area = 0, bool* toolBreak = 0)
            { return NULL; }

    // external events handling
    virtual void connectActions();

    // called once when initialized
    virtual void init() {}

protected:
    virtual void onShowRootMenu(QMenu* /*menu*/) {}

protected Q_SLOTS:
    void onShowMenu();

    virtual void updateActions() {}
};


}


#endif // ACTIONCONTROLLER_H
