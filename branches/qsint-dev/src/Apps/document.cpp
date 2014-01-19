#include "document.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include <QDebug>


namespace QSint
{


Document::Document(const DocTypeInfo& info, QObject *parent) :
    m_info(&info),
    m_modified(false),
    QObject(parent)
{
}


Document::Document(const DocTypeInfo& info, const QString& defaultName, QObject *parent) :
    m_info(&info),
    m_name(defaultName),
    m_modified(false),
    QObject(parent)
{
}


void Document::updateAfterIO(const QString& fileName)
{
    QFileInfo info(fileName);

    m_name = info.fileName();
    m_path = info.absoluteFilePath();
    m_modified = false;

    qDebug() << "Document::updateAfterIO()  " << m_path;

    // IO info changed
    emit documentChanged(this);

    // modification flag changed
    emit documentModified(this);
}


// static

bool Document::readFromFile(const QString& fileName, QString& text)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream ts(&file);
    text = ts.readAll();
    file.close();

    //qDebug() << "Document::readFromFile ok";

    return true;
}


bool Document::saveToFile(const QString& fileName, const QString& text)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream ts(&file);
    ts << text;
    file.close();

    return true;
}


}

