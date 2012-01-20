#ifndef OPENDIALOGBASE_H
#define OPENDIALOGBASE_H


#include <QtCore>


#include "documentcontroller.h"


namespace QSint
{


class OpenDialogBase : public QObject
{
public:
    virtual QStringList chooseFilesToOpen(
            const QList<DocumentController::DocFileTypeIndex>& docFilters,
            const QString& rootDir,
            bool allowAllFiles,
            int* filterIndex = 0) = 0;
};


}


#endif // OPENDIALOGBASE_H
