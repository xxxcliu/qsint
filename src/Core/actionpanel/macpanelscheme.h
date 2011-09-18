#ifndef MACPANELSCHEME_H
#define MACPANELSCHEME_H

#include "actionpanelscheme.h"


namespace QSint
{


class MacPanelScheme : public ActionPanelScheme
{
public:
    explicit MacPanelScheme();

    static ActionPanelScheme* defaultScheme()
    {
        static MacPanelScheme scheme;
        return &scheme;
    }
};


}

#endif // MACPANELSCHEME_H
