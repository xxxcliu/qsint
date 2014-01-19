#include "spinsliderplugin.h"

#include <QtCore/QtPlugin>

#include <QSint>

using namespace QSint;

SpinSliderPlugin::SpinSliderPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void SpinSliderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool SpinSliderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *SpinSliderPlugin::createWidget(QWidget *parent)
{
    return new SpinSlider(parent);
}

QString SpinSliderPlugin::name() const
{
    return QLatin1String("QSint::SpinSlider");
}

QString SpinSliderPlugin::group() const
{
    return QLatin1String("QSint Widgets");
}

QIcon SpinSliderPlugin::icon() const
{
    return QIcon(":/icons/SpinSlider.png");
}

QString SpinSliderPlugin::toolTip() const
{
    return QLatin1String("");
}

QString SpinSliderPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool SpinSliderPlugin::isContainer() const
{
    return false;
}

QString SpinSliderPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSint::SpinSlider\" name=\"spinSlider\">\n</widget>\n");
}

QString SpinSliderPlugin::includeFile() const
{
    return QLatin1String("QSint");
}
