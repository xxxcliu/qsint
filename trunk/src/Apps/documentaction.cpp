#include "documentaction.h"
#include "document.h"


namespace QSint
{


DocumentAction::DocumentAction(Document* doc) :
    QAction(doc->name(), doc),
    m_doc(doc)
{
    setCheckable(true);
}


}

