#include "testmenucontroller.h"

TestMenuController::TestMenuController(ParentClass *parent) :
    BaseClass(tr("&Test"), parent)
{
    m_actionTest1 = new QAction(tr("Test Action"), this);
}


void TestMenuController::onShowRootMenu(QMenu* menu)
{
    ADD_ACTION(menu, m_actionTest1);
}


void TestMenuController::onMenuTriggered(QAction* action)
{
    QMessageBox::information(NULL,
                             "TestMenuController",
                             tr("Triggered: %1").arg(action->text())
                             );
}
