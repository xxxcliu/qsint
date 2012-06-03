#include "pathpickerplugin.h"

#include <QtCore/QtPlugin>

#include <QSint>

using namespace QSint;

PathPickerPlugin::PathPickerPlugin(QObject *parent) :
    QObject(parent)
{
    m_initialized = false;
}

void PathPickerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PathPickerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PathPickerPlugin::createWidget(QWidget *parent)
{
    return new PathPicker(parent);
}

QString PathPickerPlugin::name() const
{
    return QLatin1String("QSint::PathPicker");
}

QString PathPickerPlugin::group() const
{
    return QLatin1String("QSint Widgets");
}

QIcon PathPickerPlugin::icon() const
{
    return QIcon(":/icons/PathPicker.png");
}

QString PathPickerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString PathPickerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool PathPickerPlugin::isContainer() const
{
    return true;
}

QString PathPickerPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSint::PathPicker\" name=\"PathPicker\">\n</widget>\n");
}

QString PathPickerPlugin::includeFile() const
{
    return QLatin1String("QSint");
}
