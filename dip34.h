#ifndef DIP34_H
#define DIP34_H
#include <QPoint>
#include "sensor.h"
#include "utils.h"
#include "devices.h"


class SensorDIP34 : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::FIRE;
    QString model = "DIP34";
public:
    SensorDIP34(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // DIP34_H
