#ifndef RELAY_S2000_SP1_H
#define RELAY_S2000_SP1_H
#include <QPoint>
#include "utils.h"
#include "smartdevice.h"
#include "devices.h"

class Relay_S2000_SP1 : public SmartDevice
{
    TypeObject type = TypeObject::PLUGGABLE_TO485;
    QString model = "S2000SP1";
    SubSystem system = SubSystem::NO_SUBSYSTEM;
public:
    Relay_S2000_SP1(SubSystem sys, QPoint pt) : SmartDevice(pt){
        system = sys;
    }
    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // RELAY_S2000_SP1_H
