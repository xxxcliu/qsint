#include "filemenucontroller.h"
#include "mainwindow.h"
#include "documentcontroller.h"

#include <QDebug>


namespace QSint
{


FileMenuController::FileMenuController(ParentClass* parent) :
    BaseClass(tr("&File"), parent)
{
    // Create actions
    m_actionExit = new QAction(tr("E&xit"), this);
    m_actionExit->setShortcut(QKeySequence::Quit);
    m_actions.push_back(m_actionExit);

    m_actionNew = new QAction(QIcon(":/files/FileNew"), tr("&New..."), this);
    m_actionNew->setShortcut(QKeySequence::New);
    m_actionNew->setStatusTip(tr("Create new file"));
    m_actions.push_back(m_actionNew);

    m_actionOpen = new QAction(QIcon(":/files/FileOpen"), tr("&Open..."), this);
    m_actionOpen->setShortcut(QKeySequence::Open);
    m_actionOpen->setStatusTip(tr("Open a file"));
    m_actions.push_back(m_actionOpen);

    m_actionReload = new QAction(QIcon(":/files/FileReload"), tr("&Reload"), this);
    m_actionReload->setShortcut(QKeySequence::Refresh);
    m_actionReload->setStatusTip(tr("Reload current file"));
    m_actions.push_back(m_actionReload);

    m_actionSave = new QAction(QIcon(":/files/FileSave"), tr("&Save"), this);
    m_actionSave->setShortcut(QKeySequence::Save);
    m_actionSave->setStatusTip(tr("Save current file"));
    m_actions.push_back(m_actionSave);

    m_actionSaveAs = new QAction(QIcon(":/files/FileSaveAs"), tr("Save As..."), this);
    m_actionSaveAs->setShortcut(QKeySequence::SaveAs);
    m_actionSaveAs->setStatusTip(tr("Save current file under new name"));
    m_actions.push_back(m_actionSaveAs);

    m_actionSaveAll = new QAction(QIcon(":/files/FileSaveAll"), tr("Save All"), this);
    m_actionSaveAll->setShortcut(QKeySequence("Ctrl+Shift+S"));
    m_actionSaveAll->setStatusTip(tr("Save all files"));
    m_actions.push_back(m_actionSaveAll);
}


// Menu

void FileMenuController::onShowRootMenu(QMenu* menu)
{
    ADD_ACTION(menu, m_actionNew);
    ADD_ACTION(menu, m_actionOpen);

    ADD_SEPARATOR(menu);

    ADD_ACTION(menu, m_actionReload);

    ADD_SEPARATOR(menu);

    ADD_ACTION(menu, m_actionSave);
    ADD_ACTION(menu, m_actionSaveAs);
    ADD_ACTION(menu, m_actionSaveAll);

    if (m_actionExit != NULL)
    {
        m_actionExit->setStatusTip(tr("Exit the %1").arg(mainWindow()->getInfo(QSint::ApplicationTitle).toString()));

        ADD_SEPARATOR(menu);
        ADD_ACTION(menu, m_actionExit);
    }
}


// Toolbars

QToolBar* FileMenuController::createToolBar(Qt::ToolBarArea* /*area*/, bool* /*toolBreak*/)
{
    m_toolbarFile = new QToolBar(tr("File"), mainWindow());

    ADD_ACTION(m_toolbarFile, m_actionNew);
    ADD_ACTION(m_toolbarFile, m_actionOpen);

    ADD_SEPARATOR(m_toolbarFile);

    ADD_ACTION(m_toolbarFile, m_actionReload);

    ADD_SEPARATOR(m_toolbarFile);

    ADD_ACTION(m_toolbarFile, m_actionSave);
    ADD_ACTION(m_toolbarFile, m_actionSaveAs);
    ADD_ACTION(m_toolbarFile, m_actionSaveAll);

    return m_toolbarFile;
}


// Actions and events

void FileMenuController::connectActions()
{
    BaseClass::connectActions();

    CONNECT_ACTION(m_actionExit, mainWindow(), close());

    DocumentController* documentCntr = documentController();
    if (documentCntr != NULL)
    {
        connect(documentCntr, SIGNAL(documentCreated(Document*)),
                this, SLOT(updateActions(Document*)));

        CONNECT_ACTION(m_actionNew, documentCntr, createFile());
        CONNECT_ACTION(m_actionOpen, documentCntr, openFile());
        CONNECT_ACTION(m_actionReload, documentCntr, reloadFile());
        CONNECT_ACTION(m_actionSave, documentCntr, saveFile());
        CONNECT_ACTION(m_actionSaveAs, documentCntr, saveFileAs());
        CONNECT_ACTION(m_actionSaveAll, documentCntr, saveAllFiles());
    }

    DocumentViewController* documentViewCntr = documentViewController();
    if (documentViewCntr != NULL)
    {
        connect(documentViewCntr, SIGNAL(documentActivated(Document*)),
                this, SLOT(updateActions(Document*)));
    }
}


void FileMenuController::updateActions(Document* doc)
{
    DocumentController* documentCntr = documentController();
    if (documentCntr != NULL)
    {
        if (m_actionNew != NULL)
            m_actionNew->setEnabled(documentCntr->canNewFile());

        if (m_actionOpen != NULL)
            m_actionOpen->setEnabled(documentCntr->canOpenFile());

        if (m_actionReload != NULL)
            m_actionReload->setEnabled(documentCntr->canReloadFile(doc));

        if (m_actionSave != NULL)
            m_actionSave->setEnabled(documentCntr->canSaveFile(doc));

        if (m_actionSaveAs != NULL)
            m_actionSaveAs->setEnabled(documentCntr->canSaveFileAs(doc));

        if (m_actionSaveAll != NULL)
            m_actionSaveAll->setEnabled(documentCntr->canSaveAllFiles());

    } else
    {
        foreach(QAction* action, m_actions)
        {
            Q_ASSERT(action != NULL);

            action->setEnabled(false);
        }
    }
}


}
