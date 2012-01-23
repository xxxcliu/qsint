#ifndef PLAINTEXTDOCUMENT_H
#define PLAINTEXTDOCUMENT_H


#include <QTextEdit>

#include "document.h"


namespace QSint
{


class PlainTextDocument : public Document
{
    Q_OBJECT
public:
    explicit PlainTextDocument(const DocTypeInfo& info, QObject *parent = 0);

    virtual QWidget* view() const
            { return m_editor; }

    virtual bool readFromFile(const QString& fileName);

protected:
    virtual void setContent(const QString& text);

protected Q_SLOTS:
    virtual void onTextChanged();

protected:
    QTextEdit* m_editor;
    QTextDocument* m_doc;
};


}


#endif // PLAINTEXTDOCUMENT_H
