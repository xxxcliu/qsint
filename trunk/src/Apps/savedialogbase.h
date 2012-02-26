#ifndef SAVEDIALOGBASE_H
#define SAVEDIALOGBASE_H


#include <QtCore>


#include "documentcontroller.h"


namespace QSint
{


class SaveDialogBase : public QObject
{
public:
    virtual QString chooseFileToSave(
        const Document& doc,
        const QList<DocumentController::DocFileTypeIndex>& docFilters,
        const QString& rootDir,
        int* filterIndex = 0) = 0;
};


}


#endif // SAVEDIALOGBASE_H
