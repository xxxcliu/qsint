#include "hypertextdocumentfactory.h"

#include <QDebug>


namespace QSint
{


HypertextDocumentFactory::HypertextDocumentFactory(QObject *parent) :
    BaseClass(parent)
{
    // this document is not creatable
    registerDocumentType(DOCTYPE_HTML, tr("HTML document"), QIcon(":/HtmlDocument"), false);
    // can only be opened & stored
    registerFileType(DOCTYPE_HTML, tr("Hypertext document"), "*.htm* *.dhtm* *.shtm*", FT_OPEN | FT_STORE);
}


}
