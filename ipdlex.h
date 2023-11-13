#ifndef IPDLEX_H
#define IPDLEX_H

#include "utils.h"
#include "sensor.h"
#include "devices.h"
#include <QPoint>

class SensorIPDLex : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::SKUD;
    QString model = "IPDLex";
public:
    SensorIPDLex(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // IPDLEX_H
