#include "documentcontroller.h"
#include "documentfactory.h"
#include "document.h"
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

    int filterIndex = -1;
    QStringList openFilesList = chooseFilesToOpen(
                m_openDocTypes,
                m_lastOpenDir,
                m_allowAllFilesFilter,
                &filterIndex);

    if (openFilesList.isEmpty())
        return;

    QString lastDir(QDir(openFilesList.first()).absolutePath());
    if (m_lastOpenDirPolicy == LDP_LAST || m_lastOpenDirPolicy == LDP_LAST_ANY)
        m_lastOpenDir = lastDir;
    if (m_lastStoreDirPolicy == LDP_LAST_ANY || m_lastStoreDirPolicy == LDP_LAST_IGNORED)
        m_lastStoreDir = lastDir;

    //qDebug() << lastDir;
    createDocuments(openFilesList, filterIndex);

    emit changed();
}


QStringList DocumentController::chooseFilesToOpen(const QList<DocFileTypeIndex>& docFilters,
                                          const QString& rootDir,
                                          bool allowAllFiles,
                                          int* filterIndex)
{
    Q_ASSERT(m_openDialog != NULL);

    if (m_openDialog == NULL)
        return QStringList();

    return m_openDialog->chooseFilesToOpen(docFilters, rootDir, allowAllFiles, filterIndex);
}


void DocumentController::createDocuments(const QStringList& openFilesList,
                                         int filterIndex)
{
    // temporary vectors
    QStringList alreadyOpenFiles;
    QList<Document*> alreadyOpenDocs;

    QStringList cantOpenFiles;

    // try to load files via corresponding factories
    int from = 0, to = m_openDocTypes.size()-1;

    // if filterIndex != -1 then use the given factory
    if (filterIndex >= 0)
    {
        from = to = filterIndex;
    }

    foreach(const QString& filename, openFilesList)
    {
        Document* doc = NULL;

        // check if already open
        if ((doc = documentOpened(filename)) != NULL)
        {
            alreadyOpenFiles.append(filename);
            alreadyOpenDocs.append(doc);
            continue;
        }

        // try to open
        for (int i = from; i <= to; i++)
        {
            const DocFileTypeIndex& index = m_openDocTypes.at(i);
            DocumentFactory* factory = index.first;

            doc = factory->createDocumentFromFile(filename);
            if (doc != NULL)
            {
                m_documents.append(doc);

                emit documentCreated(doc);
                break;
            }
        }

        // cannot open
        if (doc == NULL)
        {
            cantOpenFiles.append(filename);
            continue;
        }
    }

    // if there are already opened documents, ask to reload
    if (!alreadyOpenFiles.isEmpty())
    {
        QStringList files = showAlreadyOpenedFiles(alreadyOpenFiles);
        if (!files.isEmpty())
        {
            // reload files...
            reloadDocuments(alreadyOpenDocs);
        }
    }

    // if there are not opened documents
    if (!cantOpenFiles.isEmpty())
    {
        QStringList files = showNotOpenedFiles(cantOpenFiles);
        if (!files.isEmpty())
        {
            createDocuments(cantOpenFiles, filterIndex);
        }
    }
}


void DocumentController::reloadDocuments(const QList<Document*>& docList)
{
    QStringList cantOpenFiles;

    foreach(Document* doc, docList)
    {
        Q_ASSERT(doc != NULL);

        if (doc->readFromFile(doc->path()))
        {
            emit documentChanged(doc);
        } else
        {
            cantOpenFiles.append(doc->path());
        }
    }

    // if there are not opened documents
    if (!cantOpenFiles.isEmpty())
    {
        //showNotReloadedFiles(cantOpenFiles);
    }
}


QStringList DocumentController::showAlreadyOpenedFiles(const QStringList& filesList)
{
    QString files = filesList.join("<br>");

    int r = QMessageBox::warning(NULL,
                      tr("Already open"),
                      tr("Following documents are opened already:<br><br>%1"
                         "<br><br>Do you want to reload them?").arg(files),
                      QMessageBox::Ok, QMessageBox::Cancel
                      );

    if (r == QMessageBox::Ok)
        return filesList;

    return QStringList();
}


QStringList DocumentController::showNotOpenedFiles(const QStringList& filesList)
{
    QString files = filesList.join("<br>");

    int r = QMessageBox::critical(NULL,
                      tr("Cannot open"),
                      tr("Following documents cannot be opened:<br><br>%1"
                         "<br><br>Do you want to try again?").arg(files),
                      QMessageBox::Ok, QMessageBox::Cancel
                      );

    if (r == QMessageBox::Ok)
        return filesList;

    return QStringList();
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


// Documents

Document* DocumentController::documentOpened(const QString& filename) const
{
    if (filename.isEmpty())
        return NULL;

    QFileInfo info(filename);

    foreach (Document* doc, m_documents)
    {
        if (QFileInfo(doc->path()) == info)
            return doc;
    }

    return NULL;
}

}

