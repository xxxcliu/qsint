#ifndef ANDROIDPANELSCHEME_H
#define ANDROIDPANELSCHEME_H


#include "actionpanelscheme.h"


namespace QSint
{


class AndroidPanelScheme : public ActionPanelScheme
{
public:
    AndroidPanelScheme();

    static ActionPanelScheme* defaultScheme()
    {
        static AndroidPanelScheme scheme;
        return &scheme;
    }
};


}


#endif // ANDROIDPANELSCHEME_H
