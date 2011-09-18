#include "documentviewcontroller.h"
#include "document.h"


namespace QSint
{


DocumentViewController::DocumentViewController(QWidget *parent) :
    QTabWidget(parent)
{
}



void DocumentViewController::onDocumentsChanged()
{
}


void DocumentViewController::onDocumentCreated(Document* doc)
{
    QWidget* view = doc->view();
    Q_ASSERT(view != NULL);

    addTab(view, doc->name());
}


}

