#ifndef PLAINTEXTDOCUMENTFACTORY_H
#define PLAINTEXTDOCUMENTFACTORY_H


#include "documentfactory.h"
#include "plaintextdocument.h"


namespace QSint
{


enum PlainTextDocType {
    DOCTYPE_TEXT
};


class PlainTextDocumentFactory :
        public TDocumentFactory<PlainTextDocument, DOCTYPE_TEXT>
{
public:
    typedef TDocumentFactory<PlainTextDocument, DOCTYPE_TEXT> BaseClass;

    explicit PlainTextDocumentFactory(QObject *parent = 0);
};


}


#endif // PLAINTEXTDOCUMENTFACTORY_H
