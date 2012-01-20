#ifndef DOCUMENTFACTORY_H
#define DOCUMENTFACTORY_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QIcon>


namespace QSint
{


class DocumentFactory;
class Document;


struct DocTypeInfo
{
    // default constructor creates invalid type
    DocTypeInfo(DocumentFactory* factory = NULL, int id = -1)
    {
        this->id = id;
        create = true;
        this->factory = factory;
    }

    int id;
    QIcon icon;
    QString description;
    bool create;
    class DocumentFactory* factory;

    inline bool isValid() const
            { return id >= 0 && factory != NULL; }
};


struct DocFileInfo
{
    int id;
    QString description;
    QString filters;
    bool open;
    bool store;

    inline bool isValid() const
            { return id >= 0 && !description.isEmpty(); }
};


class DocumentFactory : public QObject
{
public:
    enum FileAccessType {
        FT_OPEN = 1,
        FT_STORE = 2
    };

    explicit DocumentFactory(QObject *parent = 0);
    virtual ~DocumentFactory();


    // returns \a true if the factory able to create documents, \a false otherwise
    virtual bool canCreateDocuments() const
            { return m_canCreate; }

    // reimplement to create the document with the type id \a id
    virtual Document* createDocument(int /*id*/)
            { return NULL; }

    // reimplement to create the document from the file \a filename
    virtual Document* createDocumentFromFile(const QString& /*filename*/)
            { return NULL; }

    // returns all the available document type infos
    const QList<DocTypeInfo*> documentTypes() const
            { return m_docTypes.values(); }

    // returns document type info for \a id, or NULL when id is unknown
    const DocTypeInfo* documentTypeInfo(int id) const;


    virtual bool canOpenDocuments() const
            { return m_canOpen; }

    virtual bool canStoreDocuments() const
            { return m_canStore; }

    const QList<DocFileInfo>& documentFileTypes() const
            { return m_fileTypes; }

protected:
    virtual bool registerDocumentType(int id, const QString& description, const QIcon& icon, bool creatable = true);
    virtual bool registerFileType(int id, const QString& description, const QString& filters, int access);

protected:
    QMap<int, DocTypeInfo*> m_docTypes;
    QList<DocFileInfo> m_fileTypes;

    bool m_canCreate, m_canOpen, m_canStore;
};


template<typename DocumentClass, int DocumentDefaultType>
class TDocumentFactory: public DocumentFactory
{
public:
    explicit TDocumentFactory(QObject *parent = 0):
        DocumentFactory(parent) {}

    virtual DocumentClass* createDocument(int id = DocumentDefaultType);
    virtual DocumentClass* createDocumentFromFile(const QString& fileName);
};


#define TDocumentFactoryClass(x) \
    template<typename DocumentClass, int DocumentDefaultType> \
    x TDocumentFactory<DocumentClass, DocumentDefaultType>


TDocumentFactoryClass(DocumentClass*)::createDocument(int id)
{
    Q_ASSERT(id == DocumentDefaultType);

    const DocTypeInfo* info = documentTypeInfo(id);
    Q_ASSERT(info != NULL);

    if (!info)
        return NULL;

    return new DocumentClass(*info, this);
}


TDocumentFactoryClass(DocumentClass*)::createDocumentFromFile(const QString& fileName)
{
    DocumentClass* doc = dynamic_cast<DocumentClass*>(createDocument(DocumentDefaultType));
    if (!doc)
        return NULL;

    if (!doc->readFromFile(fileName))
    {
        delete doc;
        return NULL;
    }

    return doc;
}


}


#endif // DOCUMENTFACTORY_H
