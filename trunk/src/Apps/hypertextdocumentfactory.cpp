#include "hypertextdocumentfactory.h"

#include <QDebug>


namespace QSint
{


HypertextDocumentFactory::HypertextDocumentFactory(QObject *parent) :
    BaseClass(parent)
{
    registerDocumentType(DOCTYPE_HTML, tr("HTML document"), QIcon(":/HtmlDocument"), /*false*/true);
    registerFileType(DOCTYPE_HTML, tr("Hypertext document"), "*.htm* *.dhtm* *.shtm*", FT_OPEN | FT_STORE);
}


}
