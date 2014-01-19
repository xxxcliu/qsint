#include "qtsavedialog.h"
#include "document.h"
#include "documentfactory.h"

#include <QFileDialog>


namespace QSint
{


QString QtSaveDialog::chooseFileToSave(
    const Document& doc,
    const QList<DocumentController::DocFileTypeIndex>& docFilters,
    const QString& rootDir,
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

    QString result = execute(
        tr("Save file %1").arg(doc.name()),
        rootDir,
        doc.path(),
        filters,
        &selectedFilter);

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


QString QtSaveDialog::execute(
    const QString& header,
    const QString& rootDir,
    const QString& defaultName,
    const QString& filters,
    QString* selectedFilter)
{
    QFileDialog fileSaveDialog(NULL, header, rootDir, filters);
    fileSaveDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileSaveDialog.setConfirmOverwrite(true);
    fileSaveDialog.selectFile(defaultName);

    if (fileSaveDialog.exec()) {
        if (selectedFilter != NULL)
            *selectedFilter = fileSaveDialog.selectedFilter();

        Q_ASSERT(!fileSaveDialog.selectedFiles().isEmpty());
        return fileSaveDialog.selectedFiles().first();
    }

    return QString();
}


}

