#include "menuactioncontroller.h"


namespace QSint
{


MenuActionController::MenuActionController(const QString& name, ParentClass *parent) :
    ActionController(parent),
    m_name(name)
{
}


// Menu

QMenu* MenuActionController::createMenu()
{
    m_menu = new QMenu(m_name);

    return m_menu;
}


}

