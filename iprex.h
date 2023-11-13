#ifndef IPREX_H
#define IPREX_H

#include "utils.h"
#include "sensor.h"
#include "devices.h"
#include <QPoint>

class SensorIPRex : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::SKUD;
    QString model = "IPRex";
public:
    SensorIPRex(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // IPREX_H
