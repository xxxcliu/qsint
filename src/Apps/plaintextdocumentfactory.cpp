#include "plaintextdocumentfactory.h"
#include "plaintextdocument.h"


namespace QSint
{


PlainTextDocumentFactory::PlainTextDocumentFactory(QObject *parent) :
    DocumentFactory(parent)
{
    registerDocumentType(DOCTYPE_TEXT, tr("Text document"), QIcon(":/TextDocument"));
    registerFileType(DOCTYPE_TEXT, tr("Plain text document"), "*.txt", FT_OPEN | FT_STORE);
}


Document* PlainTextDocumentFactory::createDocument(int id)
{
    Q_ASSERT(id == DOCTYPE_TEXT);

    return new PlainTextDocument(this);
}


}

