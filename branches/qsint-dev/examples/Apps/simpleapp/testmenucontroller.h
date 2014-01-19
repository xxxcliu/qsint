#ifndef TESTMENUCONTROLLER_H
#define TESTMENUCONTROLLER_H


#include <QSintApp>


class TestMenuController : public QSint::MenuActionController
{
    Q_OBJECT

    typedef QSint::MainWindow ParentClass;
    typedef QSint::MenuActionController BaseClass;

public:
    explicit TestMenuController(ParentClass *parent);

protected:
    virtual void onShowRootMenu(QMenu* menu);
    virtual void onMenuTriggered(QAction*);

private:
    QAction* m_actionTest1;
};

#endif // TESTMENUCONTROLLER_H
