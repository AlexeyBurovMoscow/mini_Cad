#include "iprex.h"


TypeObject SensorIPRex::getType()
{
    return type;
}

SubSystem SensorIPRex::getSubSys()
{
    return system;
}

QString SensorIPRex::getModel()
{
    return model;
}
