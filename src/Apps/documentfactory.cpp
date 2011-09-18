#include "documentfactory.h"


namespace QSint
{


DocumentFactory::DocumentFactory(QObject *parent) :
    QObject(parent)
{
    m_canCreate = m_canOpen = m_canStore = false;
}


DocumentFactory::~DocumentFactory()
{
    qDeleteAll(m_docTypes);
}


const DocTypeInfo* DocumentFactory::documentTypeInfo(int id) const
{
    if (m_docTypes.contains(id))
        return m_docTypes[id];

    return NULL;
}


bool DocumentFactory::registerDocumentType(int id,
                                           const QString& description,
                                           const QIcon& icon,
                                           bool creatable)
{
    if (description.isEmpty())
        return false;

    DocTypeInfo* info = new DocTypeInfo(this, id);
    info->description = description;
    info->icon = icon;
    info->create = creatable;

    m_docTypes[id] = info;

    if (creatable)
        m_canCreate = true;

    return true;
}


bool DocumentFactory::registerFileType(int id,
                                       const QString& description,
                                       const QString& filters,
                                       int access)
{
    if (description.isEmpty())
        return false;

    DocFileInfo info;
    info.id = id;
    info.description = description;
    info.filters = filters;
    info.open = access & FT_OPEN;
    info.store = access & FT_STORE;

    m_fileTypes.append(info);

    if (info.open)
        m_canOpen = true;
    if (info.store)
        m_canStore = true;

    return true;
}


}

