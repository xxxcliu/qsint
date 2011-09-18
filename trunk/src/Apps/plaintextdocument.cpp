#include "plaintextdocument.h"


namespace QSint
{


PlainTextDocument::PlainTextDocument(QObject *parent) :
    Document(parent)
{
    m_editor = new QTextEdit();

    m_name = tr("Text document");
}


}

