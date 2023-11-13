#ifndef FOTON4_H
#define FOTON4_H
#include "utils.h"
#include "sensor.h"
#include "devices.h"
#include <QPoint>

class SensorFoton4 : public Sensor
{
    TypeObject type = TypeObject::PLUGGABLE_TO2WIRE;
    SubSystem system = SubSystem::SKUD;
    QString model = "Foton4";
public:
    SensorFoton4(QPoint pt) : Sensor(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;


};

#endif // FOTON4_H
