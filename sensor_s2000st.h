#ifndef SENSOR_S2000ST_H
#define SENSOR_S2000ST_H

#include <QPoint>
#include "sensor.h"
#include "utils.h"
#include "devices.h"

class Sensor_S2000ST : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::FIRE;
    QString model = "S2000ST";
public:
    Sensor_S2000ST(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // SENSOR_S2000ST_H
