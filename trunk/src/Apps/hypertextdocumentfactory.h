#ifndef HYPERTEXTDOCUMENTFACTORY_H
#define HYPERTEXTDOCUMENTFACTORY_H


#include "documentfactory.h"
#include "hypertextdocument.h"


namespace QSint
{


enum HypertextDocType {
    DOCTYPE_HTML
};


class HypertextDocumentFactory :
        public TDocumentFactory<HypertextDocument, DOCTYPE_HTML>
{
public:
    typedef TDocumentFactory<HypertextDocument, DOCTYPE_HTML> BaseClass;

    explicit HypertextDocumentFactory(QObject *parent = 0);
};


}


#endif // HYPERTEXTDOCUMENTFACTORY_H
