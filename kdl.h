#ifndef KDL_H
#define KDL_H
#include "utils.h"
#include <QPoint>
#include "smartdevice.h"
#include "devices.h"

class Controller_KDL : public SmartDevice
{
    TypeObject type = TypeObject::PLUGGABLE_TO485;
    SubSystem system = SubSystem::SKUD;
    QString model = "KDL";
public:
    Controller_KDL(QPoint pt) : SmartDevice(pt){}

    TypeObject getType();
    SubSystem getSubSys();
    QString getModel() override ;
};

#endif // KDL_H
