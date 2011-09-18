#include "helpmenucontroller.h"
#include "mainwindow.h"

#include <QDebug>


namespace QSint
{


HelpMenuController::HelpMenuController(ParentClass* parent) :
    BaseClass(parent)
{
    m_actionAbout = new QAction(tr("A&bout"), this);
    connect(m_actionAbout, SIGNAL(triggered()), parent, SLOT(showAbout()));
}


QMenu* HelpMenuController::createMenu()
{
    m_menuHelp = new QMenu(tr("&Help"));

    return m_menuHelp;
}


void HelpMenuController::onShowRootMenu(QMenu* menu)
{
    menu->clear();

    if (m_actionAbout != NULL)
    {
        menu->addSeparator();

        m_actionAbout->setStatusTip(
                tr("Show information about the %1")
                        .arg(mainWindow()->getInfo(QSint::ApplicationName).toString()));

        menu->addAction(m_actionAbout);
    }
}


}
