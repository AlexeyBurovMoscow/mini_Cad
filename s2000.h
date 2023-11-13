#ifndef S2000_H
#define S2000_H
#include <QPoint>
#include "utils.h"
#include "smartdevice.h"
#include "devices.h"

class Controller_S2000 : public SmartDevice
{
    TypeObject type = TypeObject::PLUGGABLE_TO485;
    QString model = "S2000";
    SubSystem system = SubSystem::NO_SUBSYSTEM;
public:
    Controller_S2000(SubSystem sys, QPoint pt) : SmartDevice(pt){
        system = sys;
    }

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // S2000_H
