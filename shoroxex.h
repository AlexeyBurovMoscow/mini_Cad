#ifndef SHOROXEX_H
#define SHOROXEX_H

#include "utils.h"
#include "sensor.h"
#include "devices.h"
#include <QPoint>

class SensorShoroxEx : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::SKUD;
    QString model = "ShoroxEx";
public:
    SensorShoroxEx(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // SHOROXEX_H
