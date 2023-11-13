#ifndef SENSOR_S2000_SHIK_H
#define SENSOR_S2000_SHIK_H

#include <QPoint>
#include "sensor.h"
#include "utils.h"
#include "devices.h"

class Sensor_S2000SHIK : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::FIRE;
    QString model = "S2000SHIK";
public:
    Sensor_S2000SHIK(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // SENSOR_S2000_SHIK_H
