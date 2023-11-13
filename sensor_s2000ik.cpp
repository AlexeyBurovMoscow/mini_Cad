#include "sensor_s2000ik.h"

TypeObject Sensor_S2000IK::getType()
{
    return type;
}

SubSystem Sensor_S2000IK::getSubSys()
{
    return system;
}

QString Sensor_S2000IK::getModel()
{
    return model;
}
