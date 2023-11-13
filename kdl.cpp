#include "kdl.h"


TypeObject Controller_KDL::getType()
{
    return type;
}

SubSystem Controller_KDL::getSubSys()
{
    return system;
}

QString Controller_KDL::getModel()
{
    return model;
}
