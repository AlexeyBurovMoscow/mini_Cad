#ifndef CONTROLLER_S2000_4_H
#define CONTROLLER_S2000_4_H

#include <QPoint>
#include "utils.h"
#include "smartdevice.h"
#include "devices.h"

class Controller_S2000_4 : public SmartDevice
{
    TypeObject type = TypeObject::PLUGGABLE_TO485;
    QString model = "S20004";
    SubSystem system = SubSystem::NO_SUBSYSTEM;
public:
    Controller_S2000_4(SubSystem sys, QPoint pt) : SmartDevice(pt){
        system = sys;
    }
    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;

};

#endif // CONTROLLER_S2000_4_H
