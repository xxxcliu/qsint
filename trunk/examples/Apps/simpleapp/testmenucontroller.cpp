#include "testmenucontroller.h"

TestMenuController::TestMenuController(ParentClass *parent) :
    BaseClass(parent)
{
    m_actionTest1 = new QAction("Test Action", this);
}


QMenu* TestMenuController::createMenu()
{
    m_menuTest = new QMenu("&Test");

    ADD_ACTION(m_menuTest, m_actionTest1);

    return m_menuTest;
}

