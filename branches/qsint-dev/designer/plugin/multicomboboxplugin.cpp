#include "multicomboboxplugin.h"

#include <QtCore/QtPlugin>

#include <QSint>

using namespace QSint;

MultiComboBoxPlugin::MultiComboBoxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void MultiComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool MultiComboBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *MultiComboBoxPlugin::createWidget(QWidget *parent)
{
    return new MultiComboBox(parent);
}

QString MultiComboBoxPlugin::name() const
{
    return QLatin1String("QSint::MultiComboBox");
}

QString MultiComboBoxPlugin::group() const
{
    return QLatin1String("QSint Widgets");
}

QIcon MultiComboBoxPlugin::icon() const
{
    return QIcon(":/icons/MultiComboBox.png");
}

QString MultiComboBoxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString MultiComboBoxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool MultiComboBoxPlugin::isContainer() const
{
    return false;
}

QString MultiComboBoxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QSint::MultiComboBox\" name=\"MultiComboBox\">\n</widget>\n");
}

QString MultiComboBoxPlugin::includeFile() const
{
    return QLatin1String("QSint");
}
