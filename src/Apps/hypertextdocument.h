#ifndef HYPERTEXTDOCUMENT_H
#define HYPERTEXTDOCUMENT_H


#include <QTextBrowser>


#include "document.h"


namespace QSint
{



class HypertextDocument : public Document
{
    Q_OBJECT
public:
    explicit HypertextDocument(QObject *parent = 0);

    virtual QWidget* view() const
            { return m_browser; }

protected:
    QTextBrowser* m_browser;
};


}


#endif // HYPERTEXTDOCUMENT_H
