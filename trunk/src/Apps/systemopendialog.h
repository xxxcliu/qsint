#ifndef SYSTEMOPENDIALOG_H
#define SYSTEMOPENDIALOG_H


#include "qtopendialog.h"


namespace QSint
{


class SystemOpenDialog : public QtOpenDialog
{
protected:
    virtual QStringList execute(
            const QString& header,
            const QString& rootDir,
            const QString& filters,
            QString* selectedFilter);
};


}


#endif // SYSTEMOPENDIALOG_H
