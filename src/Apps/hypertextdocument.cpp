#include "hypertextdocument.h"


namespace QSint
{


HypertextDocument::HypertextDocument(QObject *parent) :
    BaseClass(parent)
{
    m_name = tr("Html document");

    m_editor->setReadOnly(true);
}


void HypertextDocument::setContent(const QString& text)
{
    m_doc->setHtml(text);
}


}
