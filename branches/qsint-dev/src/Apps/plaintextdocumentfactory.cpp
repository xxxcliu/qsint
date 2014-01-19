#include "plaintextdocumentfactory.h"

#include <QDebug>


namespace QSint
{


PlainTextDocumentFactory::PlainTextDocumentFactory(QObject *parent) :
    BaseClass(parent)
{
    registerDocumentType(DOCTYPE_TEXT, tr("Text document"), QIcon(":/TextDocument"));
    registerFileType(DOCTYPE_TEXT, tr("Plain text document"), "*.txt", FT_OPEN | FT_STORE);
}


}

