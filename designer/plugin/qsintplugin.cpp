#include "qsintplugin.h"

#include "scrollpannerplugin.h"
#include "colorgridplugin.h"
#include "colorbuttonplugin.h"
#include "actionboxplugin.h"
#include "actionlabelplugin.h"
#include "actionpanelplugin.h"
#include "actiongroupplugin.h"
#include "pathpickerplugin.h"
#include "optionsliderplugin.h"
#include "spinsliderplugin.h"

//#include "multicomboboxplugin.h"


QSintPlugin::QSintPlugin(QObject *parent) :
    QObject(parent)
{
    widgets.append(new ActionPanelPlugin(this));
    widgets.append(new ActionGroupPlugin(this));
    widgets.append(new ActionLabelPlugin(this));
    widgets.append(new ActionBoxPlugin(this));
    widgets.append(new ColorGridPlugin(this));
    widgets.append(new ColorButtonPlugin(this));
    widgets.append(new ScrollPannerPlugin(this));
    widgets.append(new PathPickerPlugin(this));
    widgets.append(new OptionSliderPlugin(this));
    widgets.append(new SpinSliderPlugin(this));
    //widgets.append(new MultiComboBoxPlugin(this));
}

Q_EXPORT_PLUGIN2(qsintplugin, QSintPlugin)
