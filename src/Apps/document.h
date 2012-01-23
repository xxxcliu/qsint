#ifndef DOCUMENT_H
#define DOCUMENT_H


#include <QWidget>


namespace QSint
{


struct DocTypeInfo;


class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(const DocTypeInfo& info, QObject *parent = 0);
    explicit Document(const DocTypeInfo& info, const QString& defaultName, QObject *parent = 0);

    // returns document type info
    const DocTypeInfo& documentTypeInfo() const
            { return *m_info; }

    const QString& name() const
            { return m_name; }

    const QString& path() const
            { return m_path; }

    bool isModified() const
            { return m_modified; }

    virtual QWidget* view() const = 0;

    virtual bool readFromFile(const QString& fileName) = 0;

signals:
    void documentModified(Document* doc);

protected:
    void setModified(bool set)
            { m_modified = set; }

    virtual void updateAfterLoad(const QString& fileName);

    static bool readFromFile(const QString& fileName, QString& text);

protected:
    const DocTypeInfo* m_info;

    QString m_name;
    QString m_path;
    bool m_modified;
};


}


#endif // DOCUMENT_H
