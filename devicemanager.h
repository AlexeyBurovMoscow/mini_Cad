#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QList>
#include "devices.h"
#include "connectionline.h"
class DeviceManager
{
private:
    DeviceManager();
    QList<Devices*> devlist;
    QList<ConnectionLine*> lineslist;
    Models model = Models::NO_MODEL;
    SubSystem subsys = SubSystem::NO_SUBSYSTEM;

public:
    static DeviceManager& instance();
    ~DeviceManager();

    void addDevice(Devices *dev);
    void addConnectionLine(ConnectionLine * line);
    void removeAll();
    QList<Devices*> &getDevices();
    QList<ConnectionLine*> &getLines();
    ConnectionLine* getConnectionLine(int i);
    void removeDevice();
    void removeLastLine();
    void removeLastDevice();
    void removeLine();
    Devices *makeItem(QPoint pt);
    Devices *makeItem(QString &str, QString &sys, QPoint pt);

    void setCurModel(Models mod);
    void setS2000SubSystem(SubSystem sub);
    void setS2000_M_SubSystem(SubSystem sub);
    void setS2000_KS_SubSystem(SubSystem sub);
    void setS2000_BI_SubSystem(SubSystem sub);
    void setS2000_BKI_SubSystem(SubSystem sub);
    void setS2000_K_SubSystem(SubSystem sub);
    void setS2000_SP1_SubSystem(SubSystem sub);
    void setS2000_4_SubSystem(SubSystem sub);
};

#endif // DEVICEMANAGER_H
