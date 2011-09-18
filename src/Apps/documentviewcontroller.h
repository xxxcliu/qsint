#ifndef DOCUMENTVIEWCONTROLLER_H
#define DOCUMENTVIEWCONTROLLER_H


#include <QTabWidget>


namespace QSint
{


class Document;


class DocumentViewController : public QTabWidget
{
    Q_OBJECT
public:
    explicit DocumentViewController(QWidget *parent = 0);

public Q_SLOTS:
    virtual void onDocumentsChanged();
    virtual void onDocumentCreated(Document* doc);
};


}


#endif // DOCUMENTVIEWCONTROLLER_H
