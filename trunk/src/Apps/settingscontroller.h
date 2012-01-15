#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H


#include <QObject>
#include <QList>
#include <QSettings>


namespace QSint
{


class Restorable
{
public:
    virtual bool store(QSettings& set) = 0;
    virtual bool restore(QSettings& set) = 0;
};


class SettingsController : public QObject
{
public:
    explicit SettingsController(QObject *parent);

    // called once when initialized
    virtual void init();

    bool registerObject(Restorable* object);

    bool restoreObjects();
    bool storeObjects();

protected:
    QList<Restorable*> m_objects;
    QString m_id;
    QString m_provider;
};


}


#endif // SETTINGSCONTROLLER_H
