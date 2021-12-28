#include "axbbattery.h"
#include "axbbatteryplugin.h"

#include <QtPlugin>

AXBBatteryPlugin::AXBBatteryPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void AXBBatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool AXBBatteryPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *AXBBatteryPlugin::createWidget(QWidget *parent)
{
    return new AXBBattery(parent);
}

QString AXBBatteryPlugin::name() const
{
    return QLatin1String("AXBBattery");
}

QString AXBBatteryPlugin::group() const
{
    return QLatin1String("MyWidget");
}

QIcon AXBBatteryPlugin::icon() const
{
    return QIcon(QLatin1String(":/rotateright.png"));
}

QString AXBBatteryPlugin::toolTip() const
{
    return QLatin1String("");
}

QString AXBBatteryPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool AXBBatteryPlugin::isContainer() const
{
    return false;
}

QString AXBBatteryPlugin::domXml() const
{
    return QLatin1String("<widget class=\"AXBBattery\" name=\"aXBBattery\">\n</widget>\n");
}

QString AXBBatteryPlugin::includeFile() const
{
    return QLatin1String("axbbattery.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(axbbatteryplugin, AXBBatteryPlugin)
#endif // QT_VERSION < 0x050000
