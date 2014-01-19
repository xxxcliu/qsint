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

    virtual bool readFromFile(const QString& /*fileName*/)
            { return false; }

    virtual bool saveToFile(const QString& /*fileName*/)
            { return false; }

signals:
    // emitted when contents of the document has been changed
    void documentModified(Document* doc);

    // emitted when document info has been changed (i.e. name/path after IO etc.)
    void documentChanged(Document* doc);

protected:
    void setModified(bool set)
            { m_modified = set; }

    virtual void updateAfterIO(const QString& fileName);

    static bool readFromFile(const QString& fileName, QString& text);
    static bool saveToFile(const QString& fileName, const QString& text);

protected:
    const DocTypeInfo* m_info;

    QString m_name;
    QString m_path;
    bool m_modified;
};


}


#endif // DOCUMENT_H
