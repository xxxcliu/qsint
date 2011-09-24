#ifndef DOCUMENTACTION_H
#define DOCUMENTACTION_H

#include <QAction>


namespace QSint
{


class Document;


class DocumentAction : public QAction
{
public:
    explicit DocumentAction(Document* doc);

    Document* document() { return m_doc; }

protected:
    Document* m_doc;
};


}


#endif // DOCUMENTACTION_H
