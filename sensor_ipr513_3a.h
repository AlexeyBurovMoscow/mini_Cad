#ifndef SENSOR_IPR513_3A_H
#define SENSOR_IPR513_3A_H

#include <QPoint>
#include "sensor.h"
#include "utils.h"
#include "devices.h"

class Sensor_IPR513_3A : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::FIRE;
    QString model = "IPR513_3A";
public:
    Sensor_IPR513_3A(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // SENSOR_IPR513_3A_H
