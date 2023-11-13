#ifndef CONNECTIONLINE_H
#define CONNECTIONLINE_H

#include <QList>
#include <QListIterator>
#include <QPoint>
#include <QLine>
#include "devices.h"

class Devices;
class ConnectionLine
{
private:
    QList<QPoint> keyptlist;    ///ключевые точки добавляются сюда при завершении очередного отрезка (по тычку мыши)
    QList<QPoint> checkPtLst;       ///расчетные точки, которыми должна подсвечиваться линия при наведении на нее курсор
    QList<Devices*> subscriberslist;
    int m_id = 0;
    int user_id = 0;
    int prev_user_id = 0;

    LineRole m_role;
    SubSystem m_sub;

    bool selected = false;
    bool catched = false;
    bool removed = false;

    int masterline_num = 0;

    void calculateLinePoints();

public:
    ConnectionLine();
    ~ConnectionLine(){}


    void rebuild();

    void addKeyPoint(QPoint &pt);

    QPoint getLastKeyPoint() const;
    QList<QPoint> &getKeyPointsList();

    void addSimplePoint(QPoint &pt);
    QList<QPoint> &getSimplePointsList();

    QList<Devices*> &getSubscribers();

    int getKeyPtLenght() const;

    void setRole(LineRole role);
    LineRole getRole();

    void setSubSystem(SubSystem ss);
    SubSystem getSubSystem();

    void setId(int id);
    int getId() const;

    void setUserId(int num);
    int getUserId() const;

    int getPrevUserId() const;

    void setMasterLineNum(int num);
    int getMasterLineNum() const;

    void setRemoved(bool rem);
    bool isRemoved();

    void setSelected(bool s);
    bool isSelected() const;

    void setCatched(bool c);
    bool isCatched();

    void addSubscriber(Devices * dev);
    void addSubscriber(int num);

    void checkLimits(QPoint &pt);
    void notifyAll();



    QPoint getStartPoint() const;

    QPoint getFinalPoint() const;

    void endLine();

};

#endif // CONNECTIONLINE_H
