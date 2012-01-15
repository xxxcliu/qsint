#include "settingscontroller.h"

#include <QCoreApplication>
#include <QDebug>


namespace QSint
{


SettingsController::SettingsController(QObject *parent) :
    QObject(parent)
{
}


void SettingsController::init()
{
    m_id = QCoreApplication::applicationName();
    m_provider = QCoreApplication::organizationName();
}


bool SettingsController::registerObject(Restorable* object)
{
    if (object && !m_objects.contains(object))
    {
        m_objects.append(object);

        return true;
    }

    return false;
}


bool SettingsController::restoreObjects()
{
    //QSettings set(m_provider, m_id);
    QSettings set;

    qDebug() << set.applicationName();
    qDebug() << set.organizationName();

    bool ok = true;

    foreach(Restorable* obj, m_objects)
    {
        ok = ok && obj->restore(set);
    }

    return ok;
}


bool SettingsController::storeObjects()
{
    //QSettings set(m_provider, m_id);
    QSettings set;

    bool ok = true;

    foreach(Restorable* obj, m_objects)
    {
        ok = ok && obj->store(set);
    }

    return ok;
}


}
