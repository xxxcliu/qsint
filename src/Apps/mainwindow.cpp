#include "mainwindow.h"
#include "settingscontroller.h"
#include "filemenucontroller.h"
#include "windowmenucontroller.h"
#include "helpmenucontroller.h"
#include "documentcontroller.h"
#include "documentviewcontroller.h"
#include "documentfactory.h"
#include "aboutdialog.h"

#include <QDebug>


#define QSINT_VERSION       0x000300aa
#define QSINT_VERSION_STR   "0.3.0 alpha"


namespace QSint
{


MainWindow::MainWindow(QWidget *parent) :
    BaseClass(parent),
    m_documentController(NULL),
    m_documentViewController(NULL),
    m_settingsController(NULL)
{
    setComponentInfo(tr("Qt Framework"),
                     tr("Copyright 2008-2012 Nokia Corporation"),
                     QT_VERSION_STR,
                     QT_VERSION);

    setComponentInfo(tr("QSint Application Framework"),
                     tr("Copyright 2011-2012 Sintegrial Technologies"),
                     QSINT_VERSION_STR,
                     QSINT_VERSION);
}


MainWindow::~MainWindow()
{
    finalize();
}


void MainWindow::initAndShow()
{
    // Main Window
    setAcceptDrops(true);   // accept drag&drop of the files by default


    // Status Bar
    QStatusBar* sb = createStatusBar();
    if (sb != NULL)
        setStatusBar(sb);


    // Documents Bar
    m_documentViewController = createDocumentBar();
    if (m_documentViewController != NULL)
    {
        setCentralWidget(m_documentViewController);

        connect(m_documentViewController, SIGNAL(documentActivated(Document*)),
                this, SLOT(onDocumentActivated(Document*)));
    }


    // Main Menu
    QMenuBar* mb = createMainMenu();
    if (mb != NULL)
        setMenuWidget(mb);


    // Document controllers
    m_documentController = createDocumentController();
    if (m_documentController != NULL && m_documentViewController != NULL)
    {
        connect(m_documentController, SIGNAL(documentCreated(Document*)),
                m_documentViewController, SLOT(onDocumentCreated(Document*)));

        connect(m_documentController, SIGNAL(documentChanged(Document*)),
                m_documentViewController, SLOT(onDocumentChanged(Document*)));

        connect(m_documentController, SIGNAL(documentModified(Document*)),
                this, SLOT(onDocumentContentChanged(Document*)));

        connect(m_documentController, SIGNAL(documentModified(Document*)),
                m_documentViewController, SLOT(onDocumentContentChanged(Document*)));
    }


    // Menu controllers
    createMenuControllers();


    // Settings controller
    m_settingsController = createSettingsController();


    // initialize settings controller
    if (m_settingsController != NULL)
    {
        // add default components
        m_settingsController->registerObject(m_documentController);
        m_settingsController->registerObject(m_documentViewController);

        m_settingsController->init();
    }


    // initialize user components (factories etc.)
    init();


    // initialize action controllers
    foreach(ActionController* cntr, m_menuControllers)
    {
        Q_ASSERT(cntr != NULL);

        // pre-init
        cntr->init();

        // create menus
        QMenu* menu = cntr->createMenu();
        if (menu != NULL && mb != NULL)
            mb->addMenu(menu);

        // create toolbars
        bool toolBreak = false;
        Qt::ToolBarArea area = Qt::TopToolBarArea;
        QToolBar* toolBar = cntr->createToolBar(&area, &toolBreak);
        if (toolBar != NULL)
        {
            addToolBar(area, toolBar);

            if (toolBreak)
                addToolBarBreak(area);
        }

        // connect
        cntr->connectActions();
    }


    // initialize document controllers has to be called after user inits
    // because the signals must be already connected
    if (m_documentController != NULL)
        m_documentController->init();

    if (m_documentViewController != NULL)
        m_documentViewController->init();


    // restore settings if available
    if (m_settingsController != NULL)
        m_settingsController->restoreObjects();


    // finally, execute
    showMaximized();
}


void MainWindow::finalize()
{
    // store settings if available
    if (m_settingsController != NULL)
        m_settingsController->storeObjects();
}


// Title

void MainWindow::updateWindowTitle()
{
    QString title;

    if (m_documentViewController != NULL)
    {
        Document* doc = m_documentViewController->activeDocument();
        if (doc != NULL)
        {
            if (doc->isModified())
            {
                if (doc->path().isEmpty())
                    title = QString("[*%1]").arg(doc->name());
                else
                    title = "*" + doc->path();
            } else
            {
                if (doc->path().isEmpty())
                    title = QString("[%1]").arg(doc->name());
                else
                    title = doc->path();
            }

            title += " - ";
        }
    }

    QString appName = m_appInfo[ApplicationTitle].toString();
    title += appName;

    setWindowTitle(title);
}


// Drag & drop

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    foreach(QUrl url, event->mimeData()->urls())
    {
        if (QFileInfo(url.toLocalFile()).exists())
        {
            event->acceptProposedAction();

            return;
        }
    }
}


void MainWindow::dropEvent(QDropEvent* event)
{
    QStringList filesToOpen;

    foreach(QUrl url, event->mimeData()->urls())
    {
        QString fileName = url.toLocalFile();
        if (QFileInfo(fileName).exists())
            filesToOpen.append(fileName);
    }

    if (!filesToOpen.isEmpty())
    {
        event->acceptProposedAction();

        if (documentController() != NULL)
            documentController()->createDocuments(filesToOpen);
    }
}


// Application information

void MainWindow::setInfo(int id, const QVariant& data)
{
    m_appInfo[id] = data;

    switch (id)
    {
    case ApplicationTitle:
        updateWindowTitle();
        break;

    case ApplicationIcon:
        setWindowIcon(qvariant_cast<QIcon>(data));
        break;
    }
}


const QVariant MainWindow::getInfo(int id) const
{
    if (m_appInfo.contains(id))
        return m_appInfo[id];

    static QVariant empty;
    return empty;
}


// Component information

void MainWindow::setComponentInfo(const QString& name, const QString& description,
                      const QString& textVersion, int numericVersion)
{
    VersionInfo compInfo;
    compInfo.name = name;
    compInfo.description = description;
    compInfo.textVersion = textVersion;
    compInfo.numericVersion = numericVersion;
    m_componentsInfo.append(compInfo);
}


// About dialog

void MainWindow::showAbout()
{
    AboutDialog aboutDialog(this);

    aboutDialog.exec();
}


// Global components

SettingsController* MainWindow::createSettingsController()
{
    return new SettingsController(this);
}


// Main menu and subcomponents

void MainWindow::createMenuControllers()
{
    //qDebug() << "MainWindow::createMenuControllers()";

    // File Menu Controller
    m_fileController = createFileMenuController();
    m_menuControllers.prepend(m_fileController);

    // Window Menu Controller
    m_windowController = createWindowMenuController();
    m_menuControllers.append(m_windowController);

    // Help Menu Controller
    m_helpController = createHelpMenuController();
    m_menuControllers.append(m_helpController);
}


bool MainWindow::registerMenuController(ActionController* cntr)
{
    if (!cntr)
        return false;

    if (!m_menuControllers.contains(cntr))
        m_menuControllers.insert(m_menuControllers.size()-1, cntr);

    return true;
}


QMenuBar* MainWindow::createMainMenu()
{
    QMenuBar* mainMenu = new QMenuBar(this);

    return mainMenu;
}


ActionController* MainWindow::createFileMenuController()
{
    return new FileMenuController(this);
}


ActionController* MainWindow::createWindowMenuController()
{
    return new WindowMenuController(this);
}


ActionController* MainWindow::createHelpMenuController()
{
    return new HelpMenuController(this);
}


// Main window subcomponents

QStatusBar* MainWindow::createStatusBar()
{
    return new QStatusBar(this);
}


DocumentViewController* MainWindow::createDocumentBar()
{
    return new DocumentViewController(this);
}


// Document subcomponents

DocumentController* MainWindow::createDocumentController()
{
    return new DocumentController(this);
}


bool MainWindow::registerDocumentFactory(DocumentFactory* factory)
{
    if (factory == NULL || m_documentController == NULL)
        return false;

    return m_documentController->addFactory(factory);
}


// Document management handlers

void MainWindow::onDocumentActivated(Document* /*doc*/)
{
    updateWindowTitle();
}


void MainWindow::onDocumentContentChanged(Document* doc)
{
    // update title for the current document only
    if (m_documentViewController != NULL)
    {
        if (doc == m_documentViewController->activeDocument())
            updateWindowTitle();
    }
}


}
