#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtGui>


namespace QSint
{


class ActionController;
class FileMenuController;
class HelpMenuController;

class DocumentViewController;
class DocumentController;
class DocumentFactory;
class Document;

class SettingsController;


struct VersionInfo
{
    QString name;
    QString description;
    QString textVersion;
    int numericVersion;
};


enum ApplicationInfo
{
    ApplicationTitle = 1000,
    ApplicationVersionNumber,
    ApplicationURL,
    ApplicationDescription,
    ApplicationCopyright,
    ApplicationIcon,
    ApplicationLogo
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

    typedef QMainWindow BaseClass;

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Explicit initialization
    virtual void initAndShow();


    // Application information
    void setInfo(int id, const QVariant& data);

    const QVariant getInfo(int id) const;

    // Component information
    void setComponentInfo(const QString& name, const QString& description,
                          const QString& textVersion, int numericVersion);

    inline const QList<VersionInfo>& componentsInfo() const
            { return m_componentsInfo; }


    // Document controller
    DocumentController* documentController() const
            { return m_documentController; }

    // Document view controller
    DocumentViewController* documentViewController() const
            { return m_documentViewController; }

    // Settings controller
    SettingsController* settingsController() const
            { return m_settingsController; }


    // Registration of user-defined components
    bool registerMenuController(ActionController* cntr);
    bool registerDocumentFactory(DocumentFactory* factory);

public Q_SLOTS:
    // About dialog
    virtual void showAbout();

    // Handles change of the current document
    virtual void onCurrentDocumentChanged(Document* doc);

protected:
    // Called once for initialization
    virtual void init() {}
    // Called once for deinitialization
    virtual void finalize();


    // Global components
    virtual SettingsController* createSettingsController();


    // Main menu and subcomponents
    virtual void createMenuControllers();

    virtual QMenuBar* createMainMenu();

    virtual ActionController* createFileMenuController();
    virtual ActionController* createWindowMenuController();
    virtual ActionController* createHelpMenuController();


    // Main window subcomponents
    virtual QStatusBar* createStatusBar();

    virtual DocumentViewController* createDocumentBar();


    // Document subcomponents
    virtual DocumentController* createDocumentController();

protected:
    // Application and components information
    QMap<int, QVariant> m_appInfo;
    QList<VersionInfo> m_componentsInfo;

    // File menu
    ActionController* m_fileController;

    // Window menu
    ActionController* m_windowController;

    // Help menu
    ActionController* m_helpController;

    // Controllers
    QList<ActionController*> m_menuControllers;
    DocumentController* m_documentController;
    DocumentViewController* m_documentViewController;
    SettingsController* m_settingsController;
};


}


#endif // MAINWINDOW_H
