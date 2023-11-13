#include "sensor_s2000smk.h"

TypeObject Sensor_S2000SMK::getType()
{
    return type;
}

SubSystem Sensor_S2000SMK::getSubSys()
{
    return system;
}

QString Sensor_S2000SMK::getModel()
{
    return model;
}
