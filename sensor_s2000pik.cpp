#include "sensor_s2000pik.h"


TypeObject Sensor_S2000PIK::getType()
{
    return type;
}

SubSystem Sensor_S2000PIK::getSubSys()
{
    return system;
}

QString Sensor_S2000PIK::getModel()
{
    return model;
}
