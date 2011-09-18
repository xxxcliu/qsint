#include "qtopendialog.h"
#include "documentfactory.h"

#include <QFileDialog>


namespace QSint
{


QStringList QtOpenDialog::openFiles(
        const QList<DocumentController::DocFileTypeIndex>& docFilters,
        const QString& rootDir,
        bool allowAllFiles)
{
    QString filters;
    foreach(const DocumentController::DocFileTypeIndex& index, docFilters)
    {
        const DocFileInfo* info = index.second;
        Q_ASSERT(info != NULL);

        filters.append(info->description + " (" + info->filters + ");;");
    }

    if (allowAllFiles)
         filters += tr("Any file") + " (*.*)";


    QString selectedFilter;

    return execute(tr("Open a file"), rootDir, filters, &selectedFilter);
}


QStringList QtOpenDialog::execute(
        const QString& header,
        const QString& rootDir,
        const QString& filters,
        QString* selectedFilter)
{
    QFileDialog fileOpenDialog(NULL, header, rootDir, filters);

    if (fileOpenDialog.exec()) {
        if (selectedFilter != NULL)
            *selectedFilter = fileOpenDialog.selectedFilter();

        return fileOpenDialog.selectedFiles();
    }

    return QStringList();
}


}

