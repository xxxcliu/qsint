#include "qtopendialog.h"
#include "documentfactory.h"

#include <QFileDialog>


namespace QSint
{


QStringList QtOpenDialog::chooseFilesToOpen(
        const QList<DocumentController::DocFileTypeIndex>& docFilters,
        const QString& rootDir,
        bool allowAllFiles,
        int* filterIndex)
{
    QString filters;
    QString selectedFilter;
    QMap<int, int> indexMap;

    for (int i = 0; i < docFilters.size(); i++)
    {
        const DocumentController::DocFileTypeIndex& index = docFilters.at(i);

        const DocFileInfo* info = index.second;
        Q_ASSERT(info != NULL);

        indexMap[filters.size()] = i;

        filters.append(info->description + " (" + info->filters + ");;");
    }

    if (allowAllFiles)
         filters += tr("Any file") + " (*.*)";

    QStringList result = execute(tr("Open a file"), rootDir, filters, &selectedFilter);

    if (filterIndex)
    {
        *filterIndex = filters.indexOf(selectedFilter);

        if (indexMap.contains(*filterIndex))
            *filterIndex = indexMap[*filterIndex];
        else
            *filterIndex = -1;

        //qDebug() << *filterIndex;
    }

    //qDebug() << selectedFilter;

    return result;
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

