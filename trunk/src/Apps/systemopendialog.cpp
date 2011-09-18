#include "systemopendialog.h"


#include <QFileDialog>


namespace QSint
{


QStringList SystemOpenDialog::execute(
        const QString& header,
        const QString& rootDir,
        const QString& filters,
        QString* selectedFilter)
{
    return QFileDialog::getOpenFileNames(NULL, header, rootDir, filters, selectedFilter);
}


}

