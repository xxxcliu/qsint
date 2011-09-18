#ifndef HYPERTEXTDOCUMENTFACTORY_H
#define HYPERTEXTDOCUMENTFACTORY_H


#include "documentfactory.h"


namespace QSint
{


class HypertextDocumentFactory : public DocumentFactory
{
public:
    enum DocType {
        DOCTYPE_HTML
    };

    explicit HypertextDocumentFactory(QObject *parent = 0);

    virtual Document* createDocument(int id);
};


}


#endif // HYPERTEXTDOCUMENTFACTORY_H
