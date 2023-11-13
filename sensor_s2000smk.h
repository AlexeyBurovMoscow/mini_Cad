#ifndef SENSOR_S2000SMK_H
#define SENSOR_S2000SMK_H

#include <QPoint>
#include "sensor.h"
#include "utils.h"
#include "devices.h"

class Sensor_S2000SMK : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::FIRE;
    QString model = "S2000SMK";
public:
    Sensor_S2000SMK(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // SENSOR_S2000SMK_H
