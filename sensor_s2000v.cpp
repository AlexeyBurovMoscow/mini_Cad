#include "sensor_s2000v.h"


TypeObject Sensor_S2000V::getType()
{
    return type;
}

SubSystem Sensor_S2000V::getSubSys()
{
    return system;
}

QString Sensor_S2000V::getModel()
{
    return model;
}
