#ifndef KEYBOARD_S2000K_H
#define KEYBOARD_S2000K_H

#include <QPoint>
#include "utils.h"
#include "smartdevice.h"
#include "devices.h"

class Keyboard_S2000K : public SmartDevice
{
    TypeObject type = TypeObject::PLUGGABLE_TO485;
    QString model = "S2000K";
    SubSystem system = SubSystem::NO_SUBSYSTEM;
public:
    Keyboard_S2000K(SubSystem sys, QPoint pt) : SmartDevice(pt){
        system = sys;
    }
    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override;
};

#endif // KEYBOARD_S2000K_H
