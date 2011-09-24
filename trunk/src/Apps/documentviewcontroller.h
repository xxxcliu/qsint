#ifndef DOCUMENTVIEWCONTROLLER_H
#define DOCUMENTVIEWCONTROLLER_H


#include <QTabWidget>
#include <QMap>


namespace QSint
{


class Document;


class DocumentViewController : public QTabWidget
{
    Q_OBJECT
public:
    explicit DocumentViewController(QWidget *parent = 0);

    Document* activeDocument();
    bool setActiveDocument(Document* doc);

public Q_SLOTS:
    virtual void onDocumentsChanged();
    virtual void onDocumentCreated(Document* doc);

protected:
    QMap<QWidget*, Document*> m_viewDocMap;
};


}


#endif // DOCUMENTVIEWCONTROLLER_H
