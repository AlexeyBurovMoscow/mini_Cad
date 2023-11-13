#include "connectionline.h"
#include <algorithm>
#include "devicemanager.h"
#include <QDebug>


void ConnectionLine::calculateLinePoints()
{
    int y = 0;

    if(keyptlist.length() > 1){

        QLine line(keyptlist.at(keyptlist.length()-2).x(),
                   keyptlist.at(keyptlist.length()-2).y(),
                   keyptlist.at(keyptlist.length()-1).x(),
                   keyptlist.at(keyptlist.length()-1).y());

        if(line.dx() >= 0){
            if((abs(line.x1() - line.x2())) <= 5){
                if(line.y1() < line.y2()){
                    for(int i = 0; i < abs(line.dy()); i++){
                        QPoint point(line.p1().x(), line.p1().y() + i);
                        addSimplePoint(point);
                    }
                }
                if(line.y1() >= line.y2()){
                    for(int i = 0; i < abs(line.dy()); i++){
                        QPoint point(line.p2().x(), line.p2().y() + i);
                        addSimplePoint(point);
                    }
                }
            }
            for(int i = 0; i < abs(line.dx()); i++){
                if(i >0){
                    double k = (double)i / (double)(abs(line.dx()));
                    y = line.p1().y() + (line.dy() * k);
                    QPoint point(line.p1().x() + i, y);
                    addSimplePoint(point);
                }
            }
        }
        else if(line.dx() < 0){
            if((abs(line.x1() - line.x2())) <= 5){
                if(line.y1() < line.y2()){
                    for(int i = 0; i < abs(line.dy()); i++){
                        QPoint point(line.p1().x(), line.p1().y() + i);
                        addSimplePoint(point);
                    }
                }
                if(line.y1() >= line.y2()){
                    for(int i = 0; i < abs(line.dy()); i++){
                        QPoint point(line.p2().x(), line.p2().y() + i);
                        addSimplePoint(point);
                    }
                }
            }
            for(int i = abs(line.dx()); i > 0; i--){
                if(i > 0){
                    double k = (double)i / (double)(abs(line.dx()));
                    y = line.p1().y() + (line.dy() * k);
                    QPoint point(line.p1().x() - i, y);
                    addSimplePoint(point);
                }
            }
        }

    }
}

ConnectionLine::ConnectionLine()
{}

void ConnectionLine::addKeyPoint(QPoint &pt)
{
    keyptlist.push_back(pt);
    calculateLinePoints();
}


QPoint ConnectionLine::getLastKeyPoint() const
{
    return keyptlist.last();
}

QList<QPoint > &ConnectionLine::getKeyPointsList()
{
    return keyptlist;
}

void ConnectionLine::addSimplePoint(QPoint &pt)
{
    QPoint pt0{pt.x(), pt.y()};
    QPoint pt1{pt.x()+1, pt.y()};
    QPoint pt2{pt.x()-1, pt.y()};
    QPoint pt3{pt.x(), pt.y()+1};
    QPoint pt4{pt.x(), pt.y()-1};
    QPoint pt5{pt.x()+2, pt.y()};
    QPoint pt6{pt.x()-2, pt.y()};
    QPoint pt7{pt.x(), pt.y()+2};
    QPoint pt8{pt.x(), pt.y()-2};

    checkPtLst.push_back(pt0);
    checkPtLst.push_back(pt1);
    checkPtLst.push_back(pt2);
    checkPtLst.push_back(pt3);
    checkPtLst.push_back(pt4);
    checkPtLst.push_back(pt5);
    checkPtLst.push_back(pt6);
    checkPtLst.push_back(pt7);
    checkPtLst.push_back(pt8);
}

QList<QPoint> &ConnectionLine::getSimplePointsList()
{
    return checkPtLst;
}

QList<Devices *> &ConnectionLine::getSubscribers()
{
    return subscriberslist;
}

int ConnectionLine::getKeyPtLenght() const
{
    return keyptlist.length();

}

void ConnectionLine::setRole(LineRole role)
{
    m_role = role;
}

LineRole ConnectionLine::getRole()
{
    return m_role;
}

void ConnectionLine::setSubSystem(SubSystem ss)
{
    m_sub = ss;
}

SubSystem ConnectionLine::getSubSystem()
{
    return m_sub;
}

void ConnectionLine::setId(int id)
{
    m_id = id;
}

int ConnectionLine::getId() const
{
    return m_id;
}

void ConnectionLine::setUserId(int num)
{
    prev_user_id = user_id;
    user_id = num;
}

int ConnectionLine::getUserId() const
{
    return user_id;
}

int ConnectionLine::getPrevUserId() const
{
    return prev_user_id;
}

void ConnectionLine::setSelected(bool s)
{
    selected = s;
}

bool ConnectionLine::isSelected() const
{
    return selected;
}

void ConnectionLine::setCatched(bool c)
{
    catched = c;
}

bool ConnectionLine::isCatched()
{
    return catched;
}

void ConnectionLine::setMasterLineNum(int num)
{
    masterline_num = num;
}

int ConnectionLine::getMasterLineNum() const
{
    return masterline_num;
}

void ConnectionLine::setRemoved(bool rem)
{
    removed = rem;
}

bool ConnectionLine::isRemoved()
{
    return removed;
}

void ConnectionLine::addSubscriber(Devices *dev)
{
    subscriberslist.push_back(dev);
}

void ConnectionLine::addSubscriber(int num)
{
    auto &manager = DeviceManager::instance();
    QListIterator<Devices*> it(manager.getDevices());
    if(!manager.getDevices().isEmpty()){
        while(it.hasNext()){
            Devices * dev = it.next();
            if(dev->getId() == num){
            subscriberslist.push_back(dev);
            }
        }
    }
}

void ConnectionLine::notifyAll()
{
    auto &manager = DeviceManager::instance();

    QListIterator<Devices*> it(subscriberslist);
    if(!subscriberslist.isEmpty()){
        while(it.hasNext()){
            Devices * dev = it.next();
            if(this->getRole() == LineRole::RS485LINE){
            dev->setNotifierId(getUserId());
            }
            else if(this->getRole() == LineRole::DUALWIRELINE){
                if(dev->getType() != TypeObject::PLUGGABLE_TO485){
                    dev->setNotifierId(getUserId());
                }
            }
        }
    }


    if(this->getRole() == LineRole::RS485LINE){
        QListIterator<Devices*> itd(manager.getDevices());
        if(!manager.getDevices().isEmpty()){
            while(itd.hasNext()){
                Devices * dev = itd.next();
                if(dev->getType() == TypeObject::PLUGGABLE_TO2WIRE){
                    if(dev->getMasterLineNum() == this->getPrevUserId()){
                        dev->setMasterLineNum(this->getUserId());
                    }
                }
            }
        }
    }
}



QPoint ConnectionLine::getStartPoint() const
{
    return keyptlist.first();
}


QPoint ConnectionLine::getFinalPoint() const
{
    return keyptlist.last();
}

void ConnectionLine::endLine()
{
    foreach (QPoint pt, keyptlist) {
        checkPtLst.push_back(pt);
    }
}

void ConnectionLine::checkLimits(QPoint &pt)
{
    auto result = std::find_if(checkPtLst.begin(), checkPtLst.end(), [=] (QPoint point){
        return point == pt;
    });

    if(result != checkPtLst.end()){
        setSelected(true);
    }
    else{
        setSelected(false);
    }
}

void ConnectionLine::rebuild()
{

}
