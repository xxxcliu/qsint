#ifndef DOCUMENTVIEWCONTROLLER_H
#define DOCUMENTVIEWCONTROLLER_H


#include <QTabWidget>
#include <QMap>

#include "settingscontroller.h"


namespace QSint
{


class Document;


class DocumentViewController : public QTabWidget, public Restorable
{
    Q_OBJECT

public:
    explicit DocumentViewController(QWidget *parent = 0);

    // Serialization
    virtual bool store(QSettings& set);
    virtual bool restore(QSettings& set);

    // Documents
    Document* activeDocument();
    bool setActiveDocument(Document* doc);

    // View setup
    void setNewTabCurrent(bool set = true)
            { m_activateNewDocument = set; }

signals:
    void currentDocumentChanged(Document* doc);

public Q_SLOTS:
    virtual void onDocumentsChanged();
    virtual void onDocumentCreated(Document* doc);
    virtual void onDocumentChanged(Document* doc);
    virtual void onDocumentContentChanged(Document* doc);

protected:
    virtual void onCurrentDocumentChanged(Document* doc);

protected Q_SLOTS:
    void onCurrentTabChanged(int index);

protected:
    QMap<QWidget*, Document*> m_viewDocMap;

    bool m_activateNewDocument;
};


}


#endif // DOCUMENTVIEWCONTROLLER_H
