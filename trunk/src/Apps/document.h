#ifndef DOCUMENT_H
#define DOCUMENT_H


#include <QWidget>


namespace QSint
{


class Document : public QObject
{
public:
    explicit Document(QObject *parent = 0);
    explicit Document(const QString& defaultName, QObject *parent = 0);

    const QString& name() const
            { return m_name; }

    const QString& path() const
            { return m_path; }

    bool isModified() const
            { return m_modified; }

    virtual QWidget* view() const = 0;

    virtual bool readFromFile(const QString& fileName) = 0;

protected:
    virtual void updateAfterLoad(const QString& fileName);

    static bool readFromFile(const QString& fileName, QString& text);

protected:
    QString m_name;
    QString m_path;
    bool m_modified;
};


}


#endif // DOCUMENT_H
