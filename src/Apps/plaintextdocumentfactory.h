#ifndef PLAINTEXTDOCUMENTFACTORY_H
#define PLAINTEXTDOCUMENTFACTORY_H


#include "documentfactory.h"


namespace QSint
{


class PlainTextDocumentFactory : public DocumentFactory
{
public:
    enum DocType {
        DOCTYPE_TEXT
    };

    explicit PlainTextDocumentFactory(QObject *parent = 0);

    virtual Document* createDocument(int id);
};


}


#endif // PLAINTEXTDOCUMENTFACTORY_H
