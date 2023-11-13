#include "sensor_s2000st.h"


TypeObject Sensor_S2000ST::getType()
{
    return type;
}

SubSystem Sensor_S2000ST::getSubSys()
{
    return system;
}

QString Sensor_S2000ST::getModel()
{
    return model;
}
