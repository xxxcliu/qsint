#include "helpmenucontroller.h"
#include "mainwindow.h"

#include <QDebug>


namespace QSint
{


HelpMenuController::HelpMenuController(ParentClass* parent) :
    BaseClass(tr("&Help"), parent)
{
    m_actionAbout = new QAction(tr("A&bout..."), this);
    m_actionAbout->setShortcut(QKeySequence::HelpContents);

    connect(m_actionAbout, SIGNAL(triggered()), parent, SLOT(showAbout()));
}


void HelpMenuController::onShowRootMenu(QMenu* menu)
{
    //menu->clear();

    if (m_actionAbout != NULL)
    {
        menu->addSeparator();

        m_actionAbout->setStatusTip(
                tr("Show information about the %1")
                        .arg(mainWindow()->getInfo(QSint::ApplicationTitle).toString()));

        menu->addAction(m_actionAbout);
    }
}


}
