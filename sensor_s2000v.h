#ifndef SENSOR_S2000V_H
#define SENSOR_S2000V_H

#include <QPoint>
#include "sensor.h"
#include "utils.h"
#include "devices.h"

class Sensor_S2000V : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::FIRE;
    QString model = "S2000V";
public:
    Sensor_S2000V(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // SENSOR_S2000V_H
