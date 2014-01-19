#include "optionsliderplugin.h"

#include <QtCore/QtPlugin>

#include <QSint>

using namespace QSint;

OptionSliderPlugin::OptionSliderPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OptionSliderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OptionSliderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OptionSliderPlugin::createWidget(QWidget *parent)
{
    return new OptionSlider(parent);
}

QString OptionSliderPlugin::name() const
{
    return QLatin1String("QSint::OptionSlider");
}

QString OptionSliderPlugin::group() const
{
    return QLatin1String("QSint Widgets");
}

QIcon OptionSliderPlugin::icon() const
{
    return QIcon(":/icons/OptionSlider.png");
}

QString OptionSliderPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OptionSliderPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OptionSliderPlugin::isContainer() const
{
    return false;
}

QString OptionSliderPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSint::OptionSlider\" name=\"optionSlider\">\n</widget>\n");
}

QString OptionSliderPlugin::includeFile() const
{
    return QLatin1String("QSint");
}
