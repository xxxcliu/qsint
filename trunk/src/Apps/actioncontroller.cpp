#include "actioncontroller.h"
#include "mainwindow.h"


namespace QSint
{


ActionController::ActionController(ParentClass* parent) :
    QObject(parent)
{
}


void ActionController::connectActions()
{
    connect(rootMenu(), SIGNAL(aboutToShow()), this, SLOT(onShowMenu()));
}


void ActionController::onShowMenu()
{
    onShowRootMenu(rootMenu());
}


}
