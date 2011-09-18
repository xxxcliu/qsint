#include "hypertextdocument.h"


namespace QSint
{


HypertextDocument::HypertextDocument(QObject *parent) :
    Document(parent)
{
    m_browser = new QTextBrowser();

    m_name = tr("Html document");
}


}

