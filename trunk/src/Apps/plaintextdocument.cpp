#include "plaintextdocument.h"


namespace QSint
{


PlainTextDocument::PlainTextDocument(QObject *parent) :
    Document(tr("Text document"), parent)
{
    m_doc = new QTextDocument(this);

    m_editor = new QTextEdit();
    m_editor->setDocument(m_doc);
}


bool PlainTextDocument::readFromFile(const QString& fileName)
{
    QString text;
    if (!Document::readFromFile(fileName, text))
        return false;

    setContent(text);

    updateAfterLoad(fileName);

    return true;
}


void PlainTextDocument::setContent(const QString& text)
{
    m_doc->setPlainText(text);
}


}

