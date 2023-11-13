#ifndef CONTROLLER_S2000_BI_H
#define CONTROLLER_S2000_BI_H

#include <QPoint>
#include "utils.h"
#include "smartdevice.h"
#include "devices.h"

class Controller_S2000_BI : public SmartDevice
{
    TypeObject type = TypeObject::PLUGGABLE_TO485;
    QString model = "S2000BI";
    SubSystem system = SubSystem::NO_SUBSYSTEM;
public:
    Controller_S2000_BI(SubSystem sys, QPoint pt) : SmartDevice(pt){
        system = sys;
    }
    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
public:
    Controller_S2000_BI();
};

#endif // CONTROLLER_S2000_BI_H
