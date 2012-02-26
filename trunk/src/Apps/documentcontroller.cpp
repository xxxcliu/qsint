#include "documentcontroller.h"
#include "documentfactory.h"
#include "document.h"

#include "qtopendialog.h"
#include "createfiledialog.h"
#include "qtsavedialog.h"

// to revise & remove !!!
#include "documentviewcontroller.h"
#include "mainwindow.h"


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

    // default save dialog
    m_saveDialog = new QtSaveDialog();
}


void DocumentController::init()
{
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


bool DocumentController::canReloadFile(Document* doc) const
{
    if (doc != NULL)
    {
        const DocTypeInfo& info = doc->documentTypeInfo();

        // can be reloaded if allowed by factory AND has been already loaded/stored
        return info.factory->canOpenDocuments() && !doc->path().isEmpty();
    }

    return false;
}


bool DocumentController::canSaveFile(Document* doc) const
{
    if (doc != NULL)
    {
        const DocTypeInfo& info = doc->documentTypeInfo();

        // can be stored if allowed by factory AND has been already loaded/stored
        return info.factory->canStoreDocuments() && doc->isModified();
    }

    return false;
}


bool DocumentController::canSaveFileAs(Document* doc) const
{
    if (doc != NULL)
    {
        const DocTypeInfo& info = doc->documentTypeInfo();

        // can be stored if allowed by factory AND has been already loaded/stored
        return info.factory->canStoreDocuments();
    }

    return false;
}


bool DocumentController::canSaveAllFiles() const
{
    foreach (Document* doc, m_documents)
    {
        Q_ASSERT(doc);

        if (canSaveFile(doc))
            return true;
    }

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

    onDocumentCreated(doc);
}


const DocTypeInfo* DocumentController::chooseNewDocumentType(
    const QList<const DocTypeInfo*>& docTypes)
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
}


QStringList DocumentController::chooseFilesToOpen(
    const QList<DocFileTypeIndex>& docFilters,
    const QString& rootDir,
    bool allowAllFiles,
    int* filterIndex)
{
    Q_ASSERT(m_openDialog != NULL);

    if (m_openDialog == NULL)
        return QStringList();

    return m_openDialog->chooseFilesToOpen(docFilters, rootDir, allowAllFiles, filterIndex);
}


void DocumentController::createDocuments(
    const QStringList& openFilesList,
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
                onDocumentCreated(doc);

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
            emit documentChanged(doc);
        else
            cantOpenFiles.append(doc->path());
    }

    // if there are not opened documents
    if (!cantOpenFiles.isEmpty())
    {
        showNotReloadedFiles(cantOpenFiles);
    }
}


QStringList DocumentController::showAlreadyOpenedFiles(const QStringList& filesList)
{
    QString files = filesList.join("<br>");

    int r = QMessageBox::warning(
                NULL,
                tr("Documents already opened"),
                tr("Following documents are opened already:<br><br>%1"
                    "<br><br>Do you want to reload them?").arg(files),
                QMessageBox::Yes,
                QMessageBox::Cancel);

    if (r == QMessageBox::Ok)
        return filesList;

    return QStringList();
}


QStringList DocumentController::showNotOpenedFiles(const QStringList& filesList)
{
    QString files = filesList.join("<br>");

    int r = QMessageBox::critical(
                NULL,
                tr("Documents not opened"),
                tr("Following documents cannot be opened:<br><br>%1"
                    "<br><br>Do you want to try again?").arg(files),
                QMessageBox::Yes,
                QMessageBox::Cancel);

    if (r == QMessageBox::Ok)
        return filesList;

    return QStringList();
}


void DocumentController::showNotReloadedFiles(const QStringList& filesList)
{
    QString files = filesList.join("<br>");

    QMessageBox::critical(
                NULL,
                tr("Cannot reload"),
                tr("Following documents cannot be reloaded:<br><br>%1").arg(files),
                QMessageBox::Ok);
}


void DocumentController::reloadFile()
{
    Document* doc = activeDocument();

    Q_ASSERT(doc != NULL);
    if (doc == NULL)
        return;

    if (doc->path().isEmpty())
        return;

    if (doc->isModified())
    {
        int r = QMessageBox::question(
                    NULL,
                    tr("Document modified"),
                    tr("The document has been modified.<br><br>"
                       "Do you really want to reload and lose the changes?"),
                    QMessageBox::Yes,
                    QMessageBox::Cancel);

        if (r == QMessageBox::Cancel)
            return;
    }

    QList<Document*> docList;
    docList << doc;
    reloadDocuments(docList);
}


void DocumentController::saveFile()
{
    Document* doc = activeDocument();

    Q_ASSERT(doc != NULL);
    if (doc == NULL)
        return;

    if (doc->path().isEmpty())
    {
        saveFileAs();
    }
    else
    {
        doSaveFile(*doc, doc->path());
    }
}


void DocumentController::saveFileAs()
{
    Document* doc = activeDocument();

    Q_ASSERT(doc != NULL);
    if (doc == NULL)
        return;

    int filterIndex = -1;   // to do...

    // allow only applicable types
    const DocTypeInfo& docInfo = doc->documentTypeInfo();

    QList<DocFileTypeIndex> docFilters;

    for (int i = 0; i < m_storeDocTypes.size(); i++)
    {
        const DocumentController::DocFileTypeIndex& index = m_storeDocTypes.at(i);

        const DocFileInfo* info = index.second;
        Q_ASSERT(info != NULL);

        // check if document id is registered as storable
        if (index.first == docInfo.factory && info->id == docInfo.id)
        {
            docFilters.append(index);
        }
    }

    // execute dialog
    QString fileName = chooseFileToSave(
                *doc,
                docFilters,
                m_lastStoreDir,
                &filterIndex);

//    qDebug() << "DocumentController::saveFileAs()";
//    qDebug() << fileName;
//    qDebug() << filterIndex;

    if (fileName.isEmpty())
        return;

    // check if the same file opened already
    Document* docToReplace = NULL;
    foreach (Document* doc2, m_documents)
    {
        if (doc2 != doc && QFileInfo(fileName) == QFileInfo(doc2->path()))
        {
            if (!showReplaceFile(*doc2, fileName))
                return;

            docToReplace = doc2;
            break;
        }
    }

    // save file under given name
    bool isSaved = doSaveFile(*doc, fileName);

    if (isSaved && docToReplace != NULL)
    {
        // close docToReplace...
    }
}


bool DocumentController::doSaveFile(Document& doc, const QString& fileName)
{
    if (!doc.saveToFile(fileName))
    {
        SaveActionRole result = showNotSavedFile(doc, fileName);
        switch(result)
        {
            case SAR_SAVEAS:
                saveFileAs();
                return false;

            case SAR_RETRY:
                saveFile();
                return false;
        }
    }

    return true;
}


QString DocumentController::chooseFileToSave(
    Document& doc,
    const QList<DocFileTypeIndex>& docFilters,
    const QString& rootDir,
    int* filterIndex)
{
    Q_ASSERT(m_saveDialog != NULL);

    if (m_saveDialog == NULL)
        return QString();

    return m_saveDialog->chooseFileToSave(doc, docFilters, rootDir, filterIndex);
}


DocumentController::SaveActionRole DocumentController::showNotSavedFile(
    const Document& doc,
    const QString& fileName)
{
    QMessageBox dialog(QMessageBox::Critical,
                tr("Document not saved"),
                tr("The document cannot be saved as %1.").arg(fileName)
    );

    //dialog.setStandardButtons(QMessageBox::Retry, QMessageBox::Ignore);
    dialog.setDefaultButton(QMessageBox::Retry);
    dialog.setEscapeButton(QMessageBox::Ignore);

    dialog.addButton(tr("Choose another name..."), QMessageBox::NRoles);

    dialog.exec();
    QMessageBox::ButtonRole r = dialog.buttonRole(dialog.clickedButton());

    switch(r)
    {
    case QMessageBox::InvalidRole:
        return SAR_CANCEL;

    case QMessageBox::Retry:
        return SAR_RETRY;
    }

    // another name by default
    return SAR_SAVEAS;
}


bool DocumentController::showReplaceFile(
        const Document& doc,
        const QString& fileName)
{
    int r = QMessageBox::warning(
                NULL,
                tr("Document already exists"),
                tr("The following document is opened already:<br><br>%1<br><br>"
                   "Do you want to replace it?").arg(fileName),
                QMessageBox::Yes | QMessageBox::Cancel);

    return (r == QMessageBox::Yes);
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


// Set save file dialog

void DocumentController::setSaveDialog(SaveDialogBase* dialog, bool deletePrevious)
{
    if (m_saveDialog != NULL && deletePrevious)
        delete m_saveDialog;

    m_saveDialog = dialog;
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
            m_createDocTypes.append(info);
    }

    const QList<DocFileInfo>& fileTypes = factory->documentFileTypes();
    foreach(const DocFileInfo& info, fileTypes)
    {
        if (info.open)
            m_openDocTypes.append(DocFileTypeIndex(factory, &info));

        if (info.store)
            m_storeDocTypes.append(DocFileTypeIndex(factory, &info));
    }

    // factory has been added successfully
    return true;
}


// Documents

Document* DocumentController::activeDocument() const
{
    ParentClass* accessor = (ParentClass*)(parent());
    if (!accessor)
        return NULL;

    if (!accessor->documentViewController())
        return NULL;

    return accessor->documentViewController()->activeDocument();
}


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


void DocumentController::onDocumentCreated(Document *doc)
{
    Q_ASSERT(doc != NULL);

    m_documents.append(doc);

    connect(doc, SIGNAL(documentModified(Document*)),
            this, SIGNAL(documentModified(Document*)));

    connect(doc, SIGNAL(documentChanged(Document*)),
            this, SIGNAL(documentChanged(Document*)));

    emit documentCreated(doc);

    emit documentChanged(doc);
}


}

