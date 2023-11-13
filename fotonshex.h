#ifndef FOTONSHEX_H
#define FOTONSHEX_H

#include "utils.h"
#include "sensor.h"
#include "devices.h"
#include <QPoint>

class SensorFotonShEx : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::SKUD;
    QString model = "FotonShEx";
public:
    SensorFotonShEx(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // FOTONSHEX_H
