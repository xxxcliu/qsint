#include "windowmenucontroller.h"
#include "mainwindow.h"
#include "documentcontroller.h"


namespace QSint
{


WindowMenuController::WindowMenuController(ParentClass* parent) :
    BaseClass(parent)
{
}


QMenu* WindowMenuController::createMenu()
{
    m_menuWindow = new QMenu(tr("&Window"));

    return m_menuWindow;
}


void WindowMenuController::onShowRootMenu(QMenu* menu)
{
}


}
