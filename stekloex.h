#ifndef STEKLOEX_H
#define STEKLOEX_H
#include "utils.h"
#include "sensor.h"
#include "devices.h"
#include <QPoint>

class SensorStekloEx : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::SKUD;
    QString model = "StekloEx";
public:
    SensorStekloEx(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // STEKLOEX_H
