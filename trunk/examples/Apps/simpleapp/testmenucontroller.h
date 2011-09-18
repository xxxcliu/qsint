#ifndef TESTMENUCONTROLLER_H
#define TESTMENUCONTROLLER_H


#include <QSintApp>


class TestMenuController : public QSint::ActionController
{
    Q_OBJECT

    typedef QSint::MainWindow ParentClass;
    typedef QSint::ActionController BaseClass;

public:
    explicit TestMenuController(ParentClass *parent);

    // menu methods
    virtual QMenu* createMenu();
    virtual QMenu* rootMenu() { return m_menuTest; }

private:
    QMenu* m_menuTest;

    QAction* m_actionTest1;
};

#endif // TESTMENUCONTROLLER_H
