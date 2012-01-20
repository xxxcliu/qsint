#include "hypertextdocument.h"


namespace QSint
{


HypertextDocument::HypertextDocument(const DocTypeInfo& info, QObject *parent) :
    BaseClass(info, parent)
{
    m_name = tr("Html document");

    m_editor->setReadOnly(true);
}


void HypertextDocument::setContent(const QString& text)
{
    m_doc->setHtml(text);
}


}
