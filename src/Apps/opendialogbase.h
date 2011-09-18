#ifndef OPENDIALOGBASE_H
#define OPENDIALOGBASE_H


#include <QtCore>


#include "documentcontroller.h"


namespace QSint
{


class OpenDialogBase : public QObject
{
public:
    virtual QStringList openFiles(
        const QList<DocumentController::DocFileTypeIndex>& docFilters,
        const QString& rootDir,
        bool allowAllFiles) = 0;
};


}


#endif // OPENDIALOGBASE_H
