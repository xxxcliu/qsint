#ifndef HYPERTEXTDOCUMENT_H
#define HYPERTEXTDOCUMENT_H


#include <QTextBrowser>


#include "plaintextdocument.h"


namespace QSint
{


class HypertextDocument : public PlainTextDocument
{
    Q_OBJECT
public:
    typedef PlainTextDocument BaseClass;

    explicit HypertextDocument(QObject *parent = 0);

protected:
    virtual void setContent(const QString& text);
};


}


#endif // HYPERTEXTDOCUMENT_H
