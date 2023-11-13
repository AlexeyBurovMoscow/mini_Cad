#include "s2000.h"


TypeObject Controller_S2000::getType()
{
    return type;
}

SubSystem Controller_S2000::getSubSys()
{
    return system;
}

QString Controller_S2000::getModel()
{
    return model;
}
