#ifndef CREATEDIALOGBASE_H
#define CREATEDIALOGBASE_H


#include <QtCore>


#include "documentfactory.h"


namespace QSint
{


class CreateDialogBase
{
public:
    virtual const DocTypeInfo* createFile(const QList<const DocTypeInfo*>& docTypes) = 0;
};


}


#endif // CREATEDIALOGBASE_H
