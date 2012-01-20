#ifndef QTOPENDIALOG_H
#define QTOPENDIALOG_H


#include "opendialogbase.h"


namespace QSint
{


class QtOpenDialog : public OpenDialogBase
{
public:
    virtual QStringList chooseFilesToOpen(
            const QList<DocumentController::DocFileTypeIndex>& docFilters,
            const QString& rootDir,
            bool allowAllFiles,
            int* filterIndex = 0);

protected:
    virtual QStringList execute(
            const QString& header,
            const QString& rootDir,
            const QString& filters,
            QString* selectedFilter);
};


}


#endif // QTOPENDIALOG_H
