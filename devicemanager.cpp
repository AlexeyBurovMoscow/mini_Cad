#include "devicemanager.h"
#include "smartdevice.h"
#include "sensor.h"
#include "s2000.h"
#include "controller_s2000_m.h"
#include "controller_s2000_ks.h"
#include "controller_s2000_bi.h"
#include "controller_s2000_bki.h"
#include "relay_s2000_sp1.h"
#include "keyboard_s2000k.h"
#include "controller_s2000_4.h"
#include "kdl.h"
#include "foton4.h"
#include "dip34.h"
#include "sensor_s2000_ip02.h"
#include "sensor_ipr513_3a.h"
#include "sensor_s2000ik.h"
#include "sensor_s2000pik.h"
#include "sensor_s2000_shik.h"
#include "sensor_s2000v.h"
#include "sensor_s2000st.h"
#include "sensor_s2000smk.h"
#include "sensor_s2000kt.h"
#include "fotonshex.h"
#include "stekloex.h"
#include "shoroxex.h"
#include "mkex.h"
#include "stzex.h"
#include "ipdex.h"
#include "ipdlex.h"
#include "ippex.h"
#include "iprex.h"
#include <QDebug>

DeviceManager::DeviceManager()
{}

DeviceManager::~DeviceManager()
{}

DeviceManager &DeviceManager::instance()
{
    static DeviceManager devmanager;
    return devmanager;
}

void DeviceManager::addDevice(Devices *dev)
{
    devlist.push_back(dev);
}

void DeviceManager::addConnectionLine(ConnectionLine *line)
{
    lineslist.push_back(line);
}

void DeviceManager::removeAll()
{
    devlist.clear();
    lineslist.clear();
}

QList<Devices *> &DeviceManager::getDevices()
{
    return devlist;
}

QList<ConnectionLine *> &DeviceManager::getLines()
{
    return lineslist;
}

ConnectionLine *DeviceManager::getConnectionLine(int i)
{
    return lineslist.at(i);
}

void DeviceManager::removeDevice()
{
    qDebug() << "removeDevice()";
    QListIterator<Devices*> it(devlist);
    if(!devlist.isEmpty()){
        while(it.hasNext()){
            Devices * dev = it.next();
            if(dev->isSelected() && (!dev->isRemoved())){
                int id = dev->getId();
                qDebug() << "removing device" << dev->getId();
                devlist.at(id)->setRemoved(true);
                devlist.at(id)->setSelected(false);
            }
        }
    }
}

void DeviceManager::removeLastLine()
{
    lineslist.removeLast();
}

void DeviceManager::removeLastDevice()
{
    devlist.removeLast();
}

void DeviceManager::removeLine()
{
    QListIterator<ConnectionLine*> itl(lineslist);
    if(!lineslist.isEmpty()){
        while(itl.hasNext()){
            ConnectionLine * line = itl.next();
            if(line->isSelected() && (!line->isRemoved())){
                int id = line->getId();
                lineslist.at(id)->setRemoved(true);
                lineslist.at(id)->setSelected(false);
            }
        }
    }
}

void DeviceManager::setCurModel(Models mod)
{
    switch (mod) {
    case Models::S2000_IP02:
    {
        model = Models::S2000_IP02;
        break;
    }
    case Models::IPR513_3A:
    {
        model = Models::IPR513_3A;
        break;
    }
    case Models::S_2000_IK:
    {
        model = Models::S_2000_IK;
        break;
    }
    case Models::S_2000_PIK:
    {
        model = Models::S_2000_PIK;
        break;
    }
    case Models::S_2000_SHIK:
    {
        model = Models::S_2000_SHIK;
        break;
    }
    case Models::S_2000_V:
    {
        model = Models::S_2000_V;
        break;
    }
    case Models::S_2000_ST:
    {
        model = Models::S_2000_ST;
        break;
    }
    case Models::S_2000_SMK:
    {
        model = Models::S_2000_SMK;
        break;
    }
    case Models::S_2000_KT:
    {
        model = Models::S_2000_KT;
        break;
    }

    case Models::S_2000_SP1:
    {
        model = Models::S_2000_SP1;
        break;
    }
    case Models::S_2000_K:
    {
        model = Models::S_2000_K;
        break;
    }
    case Models::S_2000_4:
    {
        model = Models::S_2000_4;
        break;
    }
    case Models::S_2000_BKI:
    {
        model = Models::S_2000_BKI;
        break;
    }
    case Models::S_2000_BI:
    {
        model = Models::S_2000_BI;
        break;
    }
    case Models::S_2000_KS:
    {
        model = Models::S_2000_KS;
        break;
    }
    case Models::S_2000_M:
    {
        model = Models::S_2000_M;
        break;
    }
    case Models::S_2000:
    {
        model = Models::S_2000;
        break;
    }
    case Models::KDL:
    {
        model = Models::KDL;
        break;
    }
    case Models::DIP34:
    {
        model = Models::DIP34;
        break;
    }
    case Models::FOTON4:
    {
        model = Models::FOTON4;
        break;
    }
    case Models::FotonShEx:
    {
        model = Models::FotonShEx;
        break;
    }
    case Models::StekloEx:
    {
        model = Models::StekloEx;
        break;
    }
    case Models::ShoroxEx:
    {
        model = Models::ShoroxEx;
        break;
    }
    case Models::MkEx:
    {
        model = Models::MkEx;
        break;
    }
    case Models::STZex:
    {
        model = Models::STZex;
        break;
    }
    case Models::IPDex:
    {
        model = Models::IPDex;
        break;
    }
    case Models::IPDLex:
    {
        model = Models::IPDLex;
        break;
    }
    case Models::IPPex:
    {
        model = Models::IPPex;
        break;
    }
    case Models::IPRex:
    {
        model = Models::IPRex;
        break;
    }
    default:
        break;
    }
}


Devices *DeviceManager::makeItem(QPoint pt)
{
    Devices * dev = nullptr;
    switch (model) {
    case Models::S_2000_SP1:
    {
        dev = new Relay_S2000_SP1(subsys, pt);
        break;
    }
    case Models::S_2000_4:
    {
        dev = new Controller_S2000_4(subsys, pt);
        break;
    }
    case Models::S_2000_K:
    {
        dev = new Keyboard_S2000K(subsys, pt);
        break;
    }
    case Models::S_2000_BKI:
    {
        dev = new Controller_S2000_BKI(subsys, pt);
        break;
    }
    case Models::S_2000_BI:
    {
        dev = new Controller_S2000_BI(subsys, pt);
        break;
    }
    case Models::S_2000_M:
    {
        dev = new Controller_S2000_M(subsys, pt);
        break;
    }
    case Models::S_2000:
    {
        dev =  new Controller_S2000(subsys, pt);
        break;
    }
    case Models::S_2000_KS:
    {
        dev = new Controller_S2000_KS(subsys, pt);
        break;
    }
    case Models::KDL:
    {
        dev = new Controller_KDL(pt);
        break;
    }
    case Models::DIP34:
    {
        dev = new SensorDIP34(pt);
        break;
    }
    case Models::S2000_IP02:
    {
        dev = new Sensor_S2000_IP02(pt);
        break;
    }
    case Models::IPR513_3A:
    {
        dev = new Sensor_IPR513_3A(pt);
        break;
    }
    case Models::S_2000_IK:
    {
        dev = new Sensor_S2000IK(pt);
        break;
    }
    case Models::S_2000_PIK:
    {
        dev = new Sensor_S2000PIK(pt);
        break;
    }
    case Models::S_2000_SHIK:
    {
        dev = new Sensor_S2000SHIK(pt);
        break;
    }
    case Models::S_2000_V:
    {
        dev = new Sensor_S2000V(pt);
        break;
    }
    case Models::S_2000_ST:
    {
        dev = new Sensor_S2000ST(pt);
        break;
    }
    case Models::S_2000_SMK:
    {
        dev = new Sensor_S2000SMK(pt);
        break;
    }
    case Models::S_2000_KT:
    {
        dev = new Sensor_S2000KT(pt);
        break;
    }
    case Models::FOTON4:
    {
        dev = new SensorFoton4(pt);
        break;
    }
    case Models::FotonShEx:
    {
        dev = new SensorFotonShEx(pt);
        break;
    }
    case Models::StekloEx:
    {
        dev = new SensorStekloEx(pt);
        break;
    }
    case Models::ShoroxEx:
    {
        dev = new SensorShoroxEx(pt);
        break;
    }
    case Models::MkEx:
    {
        dev = new SensorMkEx(pt);
        break;
    }
    case Models::STZex:
    {
        dev = new SensorSTZex(pt);
        break;
    }
    case Models::IPDex:
    {
        dev = new SensorIPDex(pt);
        break;
    }
    case Models::IPDLex:
    {
        dev = new SensorIPDLex(pt);
        break;
    }
    case Models::IPPex:
    {
        dev = new SensorIPPex(pt);
        break;
    }
    case Models::IPRex:
    {
        dev = new SensorIPRex(pt);
        break;
    }
    default:
        break;
    }
    return dev;
}

Devices *DeviceManager::makeItem(QString& str, QString& sys, QPoint pt)
{
    Devices * dev = nullptr;
    SubSystem sub = SubSystem::NO_SUBSYSTEM;
    ///-----подсистема--------
    if(sys == "fire"){
        sub = SubSystem::FIRE;
    }
    if(sys == "skud"){
        sub = SubSystem::SKUD;
    }
    ///-------модель устройства--------
    if(str == "S2000BKI"){
        dev = new Controller_S2000_BKI(sub, pt);
    }
    if(str == "S2000K")
    {
        dev = new Keyboard_S2000K(sub, pt);
    }
    if(str == "S20004")
    {
        dev = new Controller_S2000_4(sub, pt);
    }
    if(str == "S2000SP1")
    {
        dev = new Relay_S2000_SP1(sub, pt);
    }
    if(str == "S2000BI")
    {
        dev = new Controller_S2000_BI(sub, pt);
    }
    if(str == "S2000M")
    {
        dev = new Controller_S2000_M(sub, pt);
    }
    if(str == "S2000")
    {
        dev = new Controller_S2000(sub, pt);
    }
    if (str == "S2000KS")
    {
        dev = new Controller_S2000_KS(sub, pt);
    }
    if(str == "KDL")
    {
        dev = new Controller_KDL(pt);
    }
    if(str == "DIP34")
    {
        dev = new SensorDIP34(pt);
    }
    if(str == "S2000IP02")
    {
        dev = new Sensor_S2000_IP02(pt);
    }
    if(str == "IPR513_3A")
    {
        dev = new Sensor_IPR513_3A(pt);
    }
    if(str == "S2000IK")
    {
        dev = new Sensor_S2000IK(pt);
    }
    if(str == "S2000PIK")
    {
        dev = new Sensor_S2000PIK(pt);
    }
    if(str == "S2000SHIK")
    {
        dev = new Sensor_S2000SHIK(pt);
    }
    if(str == "S2000V")
    {
        dev = new Sensor_S2000V(pt);
    }
    if(str == "S2000ST")
    {
        dev = new Sensor_S2000ST(pt);
    }
    if(str == "S2000SMK")
    {
        dev = new Sensor_S2000SMK(pt);
    }
    if(str == "S2000KT")
    {
        dev = new Sensor_S2000KT(pt);
    }
    if(str == "Foton4")
    {
        dev = new SensorFoton4(pt);
    }
    if(str == "FotonShEx")
    {
        dev = new SensorFotonShEx(pt);
    }
    if(str == "StekloEx")
    {
        dev = new SensorStekloEx(pt);
    }
    if(str == "ShoroxEx")
    {
        dev = new SensorShoroxEx(pt);
    }
    if(str == "MkEx")
    {
        dev = new SensorMkEx(pt);
    }
    if(str == "STZex")
    {
        dev = new SensorSTZex(pt);
    }
    if(str == "IPDex")
    {
        dev = new SensorIPDex(pt);
    }
    if(str == "IPDLex")
    {
        dev = new SensorIPDLex(pt);
    }
    if(str == "IPPex")
    {
        dev = new SensorIPPex(pt);
    }
    if(str == "IPRex")
    {
        dev = new SensorIPRex(pt);
    }
    return dev;
}

void DeviceManager::setS2000SubSystem(SubSystem sub)
{
    subsys = sub;
}

void DeviceManager::setS2000_M_SubSystem(SubSystem sub)
{
    subsys = sub;
}

void DeviceManager::setS2000_KS_SubSystem(SubSystem sub)
{
    subsys = sub;
}

void DeviceManager::setS2000_BI_SubSystem(SubSystem sub)
{
    subsys = sub;
}

void DeviceManager::setS2000_BKI_SubSystem(SubSystem sub)
{
    subsys = sub;
}

void DeviceManager::setS2000_K_SubSystem(SubSystem sub)
{
    subsys = sub;
}

void DeviceManager::setS2000_SP1_SubSystem(SubSystem sub)
{
    subsys = sub;
}

void DeviceManager::setS2000_4_SubSystem(SubSystem sub)
{
    subsys = sub;
}


