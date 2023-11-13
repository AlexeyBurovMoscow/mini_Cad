#include "mkex.h"

TypeObject SensorMkEx::getType()
{
    return type;
}

SubSystem SensorMkEx::getSubSys()
{
    return system;
}

QString SensorMkEx::getModel()
{
    return model;
}
