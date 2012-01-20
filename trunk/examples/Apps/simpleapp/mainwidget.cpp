#include "mainwidget.h"
#include "testmenucontroller.h"

#include <QDebug>


MainWidget::MainWidget(QWidget *parent) : BaseClass(parent)
{
    QCoreApplication::setApplicationName("QSintAppsDemo");
    QCoreApplication::setApplicationVersion("0.1.0 alpha");
    QCoreApplication::setOrganizationName("Sintegrial");

    setInfo(QSint::ApplicationTitle, "QSintApps Demo");
    setInfo(QSint::ApplicationVersionNumber, 0x000100);
    setInfo(QSint::ApplicationURL, "http://www.sintegrial.com");
    setInfo(QSint::ApplicationDescription,
            "Sintegrial Qt Application Framework - "
            "rapid development of the multidocument applications, "
            "easy-to-use and powerful widgets, and more. "
            "Ideal solution for Qt developers.");
    setInfo(QSint::ApplicationCopyright, "&copy; 2011-2012 Sintegrial Technologies");
    setInfo(QSint::ApplicationLogo, QPixmap(":/QSintLogo"));
}


void MainWidget::init()
{
    // test menu controller
    m_testMenuCntr = new TestMenuController(this);
    registerMenuController(m_testMenuCntr);

    // document factories
    registerDocumentFactory(new QSint::PlainTextDocumentFactory(this));
    registerDocumentFactory(new QSint::HypertextDocumentFactory(this));

    // document open & save
    documentController()->setLastOpenDir("c:\\", QSint::DocumentController::LDP_LAST);
    documentController()->setLastStoreDir("g:\\temp", QSint::DocumentController::LDP_LAST_ANY);

    documentController()->setOpenDialog(new QSint::SystemOpenDialog());

    // view of tabs
    documentViewController()->setTabsClosable(true);
    //documentViewController()->setNewTabCurrent(false);

    // ready!
    //statusBar()->showMessage(getInfo(QSint::ApplicationName).toString() + " started :)");
}

