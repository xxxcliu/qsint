#include "documentcontroller.h"
#include "documentfactory.h"
#include "mainwindow.h"
#include "qtopendialog.h"
#include "createfiledialog.h"


namespace QSint
{


DocumentController::DocumentController(ParentClass *parent) :
    QObject(parent)
{
    m_allowAllFilesFilter = true;

    m_lastOpenDir = m_lastStoreDir = ".";
    m_lastOpenDirPolicy = m_lastStoreDirPolicy = LDP_LAST_ANY;

    // default open dialog
    m_openDialog = new QtOpenDialog();

    // default create dialog
    m_createDialog = new CreateFileDialog();
}


void DocumentController::init()
{
    emit changed();
}


// Serialization

bool DocumentController::store(QSettings& set)
{
    set.beginGroup("Documents");
    set.setValue("LastOpenDirectory", m_lastOpenDir);
    set.endGroup();

    return true;
}


bool DocumentController::restore(QSettings& set)
{
    set.beginGroup("Documents");
    m_lastOpenDir = set.value("LastOpenDirectory", m_lastOpenDir).toString();
    set.endGroup();

    return true;
}


// File actions availability

bool DocumentController::canNewFile() const
{
    foreach(DocumentFactory* factory, m_factories)
    {
        Q_ASSERT(factory != NULL);

        if (factory->canCreateDocuments())
            return true;
    }

    return false;
}


bool DocumentController::canOpenFile() const
{
    foreach(DocumentFactory* factory, m_factories)
    {
        Q_ASSERT(factory != NULL);

        if (factory->canOpenDocuments())
            return true;
    }

    return false;
}


bool DocumentController::canReloadFile() const
{
    return false;
}


bool DocumentController::canSaveFile() const
{
    return false;
}


bool DocumentController::canSaveFileAs() const
{
    return false;
}


bool DocumentController::canSaveAllFiles() const
{
    return false;
}


// File actions processing

void DocumentController::createFile()
{
    Q_ASSERT(!m_createDocTypes.isEmpty());

    const DocTypeInfo* info = chooseNewDocumentType(m_createDocTypes);
    if (!info)
        return;

    //qDebug() << info->description;
    Document* doc = info->factory->createDocument(info->id);
    Q_ASSERT(doc != NULL);

    m_documents.append(doc);

    emit documentCreated(doc);
    emit changed();
}


const DocTypeInfo* DocumentController::chooseNewDocumentType(const QList<const DocTypeInfo*>& docTypes)
{
    if (docTypes.count() == 1)
        return docTypes.first();

    // here show the dialog
    if (m_createDialog != NULL)
        return m_createDialog->createFile(docTypes);

    return NULL;
}


void DocumentController::openFile()
{
    Q_ASSERT(!m_openDocTypes.isEmpty());

    QStringList openFilesList = openFiles(m_openDocTypes, m_lastOpenDir, m_allowAllFilesFilter);
    if (openFilesList.isEmpty())
        return;

    QString lastDir(QDir(openFilesList.first()).absolutePath());
    if (m_lastOpenDirPolicy == LDP_LAST || m_lastOpenDirPolicy == LDP_LAST_ANY)
        m_lastOpenDir = lastDir;
    if (m_lastStoreDirPolicy == LDP_LAST_ANY || m_lastStoreDirPolicy == LDP_LAST_IGNORED)
        m_lastStoreDir = lastDir;

    qDebug() << lastDir;

    // try to load files via corresponding factories
    foreach(const QString& filename, openFilesList)
    {
        Document* doc = NULL;

        foreach(const DocFileTypeIndex& index, m_openDocTypes)
        {
            DocumentFactory* factory = index.first;
            doc = factory->createDocumentFromFile(filename);
            if (doc != NULL)
            {
                m_documents.append(doc);

                emit documentCreated(doc);

                //qDebug() << filename;

                break;
            }
        }

        // cannot open the document: warn here
        if (doc == NULL)
        {
            QMessageBox::critical(NULL,
                              tr("Cannot open file"),
                              tr("Document ""%1"" could not be opened").arg(filename)
                              );
        }
    }

    emit changed();
}


QStringList DocumentController::openFiles(const QList<DocFileTypeIndex>& docFilters,
                                          const QString& rootDir,
                                          bool allowAllFiles)
{
    Q_ASSERT(m_openDialog != NULL);

    if (m_openDialog == NULL)
        return QStringList();

    return m_openDialog->openFiles(docFilters, rootDir, allowAllFiles);
}


// Last dir policies management

void DocumentController::setLastOpenDir(const QString& dirName, LastDirPolicy policy)
{
   m_lastOpenDir = dirName;
   m_lastOpenDirPolicy = policy;
}


void DocumentController::setLastStoreDir(const QString& dirName, LastDirPolicy policy)
{
    m_lastStoreDir = dirName;
    m_lastStoreDirPolicy = policy;
}


// Set create file dialog

void DocumentController::setCreateDialog(CreateDialogBase* dialog, bool deletePrevious)
{
    if (m_createDialog != NULL && deletePrevious)
        delete m_createDialog;

    m_createDialog = dialog;
}


// Set open file dialog

void DocumentController::setOpenDialog(OpenDialogBase* dialog, bool deletePrevious)
{
    if (m_openDialog != NULL && deletePrevious)
        delete m_openDialog;

    m_openDialog = dialog;
}



// Document factories management

bool DocumentController::addFactory(DocumentFactory* factory)
{
    if (factory == NULL || m_factories.contains(factory))
        return false;

    m_factories.append(factory);

    // we will index all the document types to provide faster access
    const QList<DocTypeInfo*>& types = factory->documentTypes();
    foreach(DocTypeInfo* info, types)
    {
        Q_ASSERT(info != NULL);
        Q_ASSERT(info->isValid());

        if (info->create)
        {
            m_createDocTypes.append(info);
        }
    }

    const QList<DocFileInfo>& fileTypes = factory->documentFileTypes();
    foreach(const DocFileInfo& info, fileTypes)
    {
        if (info.open)
        {
            m_openDocTypes.append(DocFileTypeIndex(factory, &info));
        }
    }

    // factory has been added successfully
    emit changed();

    return true;
}


}

