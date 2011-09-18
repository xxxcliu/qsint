#include "hypertextdocumentfactory.h"
#include "hypertextdocument.h"


namespace QSint
{


HypertextDocumentFactory::HypertextDocumentFactory(QObject *parent) :
    DocumentFactory(parent)
{
    registerDocumentType(DOCTYPE_HTML, tr("HTML document"), QIcon(":/HtmlDocument"), /*false*/true);
    registerFileType(DOCTYPE_HTML, tr("Hypertext document"), "*.htm* *.dhtm* *.shtm*", FT_OPEN | FT_STORE);
}


Document* HypertextDocumentFactory::createDocument(int id)
{
    Q_ASSERT(id == DOCTYPE_HTML);

    return new HypertextDocument(this);
}


}
