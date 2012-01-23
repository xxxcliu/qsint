#ifndef FILEMENUCONTROLLER_H
#define FILEMENUCONTROLLER_H


#include "menuactioncontroller.h"


namespace QSint
{


class MainWindow;
class DocumentController;


class FileMenuController : public MenuActionController
{
    typedef MenuActionController BaseClass;
    typedef MainWindow ParentClass;

    Q_OBJECT
public:
    explicit FileMenuController(ParentClass *parent);

    // toolbar methods
    virtual QToolBar* createToolBar(Qt::ToolBarArea* area = 0, bool* toolBreak = 0);

    // external events handling
    virtual void connectActions();

protected:
    virtual void onShowRootMenu(QMenu* menu);

protected Q_SLOTS:
    virtual void updateActions(Document*);

protected:
    QToolBar* m_toolbarFile;

    QAction* m_actionNew;
    QAction* m_actionOpen;
    QAction* m_actionReload;
    QAction* m_actionSave;
    QAction* m_actionSaveAs;
    QAction* m_actionSaveAll;
    QAction* m_actionExit;

    QList<QAction*> m_actions;
};


}


#endif // FILEMENUCONTROLLER_H
