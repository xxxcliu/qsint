#ifndef WinXPPanelScheme_H
#define WinXPPanelScheme_H

#include "actionpanelscheme.h"


namespace QSint
{


class WinXPPanelScheme : public ActionPanelScheme
{
public:
    WinXPPanelScheme();

    static ActionPanelScheme* defaultScheme()
    {
        static WinXPPanelScheme scheme;
        return &scheme;
    }
};


class WinXPPanelScheme2 : public ActionPanelScheme
{
public:
    WinXPPanelScheme2();

    static ActionPanelScheme* defaultScheme()
    {
        static WinXPPanelScheme2 scheme;
        return &scheme;
    }
};


}

#endif // WinXPPanelScheme_H
