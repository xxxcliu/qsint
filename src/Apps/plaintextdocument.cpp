#include "plaintextdocument.h"

#include <QDebug>


namespace QSint
{


PlainTextDocument::PlainTextDocument(const DocTypeInfo& info, QObject *parent) :
    Document(info, tr("Text document"), parent)
{
    m_doc = new QTextDocument(this);

    m_editor = new QTextEdit();
    m_editor->setDocument(m_doc);

    connect(m_editor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}


bool PlainTextDocument::readFromFile(const QString& fileName)
{
    QString text;
    if (!Document::readFromFile(fileName, text))
        return false;

    setContent(text);

    updateAfterIO(fileName);

    return true;
}


bool PlainTextDocument::saveToFile(const QString& fileName)
{
    if (!Document::saveToFile(fileName, m_doc->toPlainText()))
        return false;

    updateAfterIO(fileName);

    return true;
}


void PlainTextDocument::setContent(const QString& text)
{
    m_doc->blockSignals(true);

    m_doc->setPlainText(text);
    m_doc->setModified(false);

    m_doc->blockSignals(false);
}


// Internal slots

void PlainTextDocument::onTextChanged()
{
//    qDebug() << "PlainTextDocument::onTextChanged() " << m_modified;

    if (m_modified != m_doc->isModified())
    {
        m_modified = m_doc->isModified();

//        qDebug() << "modified: " << m_modified;

        emit documentChanged(this);
    }

    emit documentModified(this);
}


}

