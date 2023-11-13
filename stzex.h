#ifndef STZEX_H
#define STZEX_H

#include "utils.h"
#include "sensor.h"
#include "devices.h"
#include <QPoint>

class SensorSTZex : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::SKUD;
    QString model = "STZex";
public:
     SensorSTZex(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // STZEX_H
