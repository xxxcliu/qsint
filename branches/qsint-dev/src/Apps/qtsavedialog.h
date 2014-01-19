#ifndef QTSAVEDIALOG_H
#define QTSAVEDIALOG_H


#include "savedialogbase.h"


namespace QSint
{


class QtSaveDialog : public SaveDialogBase
{
public:
    virtual QString chooseFileToSave(
        const Document& doc,
        const QList<DocumentController::DocFileTypeIndex>& docFilters,
        const QString& rootDir,
        int* filterIndex = 0);

protected:
    virtual QString execute(
        const QString& header,
        const QString& rootDir,
        const QString& defaultName,
        const QString& filters,
        QString* selectedFilter);
};


}


#endif // QTOPENDIALOG_H
