#include "devices.h"


Devices::~Devices()
{

}

void Devices::setUserId(int num)
{
    user_id = num;
}

int Devices::getUserId() const
{
    return user_id;
}

void Devices::setWidth(int w)
{
    width = w;
}

int Devices::getWidth() const
{
    return width;
}

void Devices::setHeight(int h)
{
    height = h;
}

int Devices::getHeight() const
{
    return height;
}

int Devices::getId() const
{
    return id;
}

void Devices::setId(const int cnt)
{
    id = cnt;
}

void Devices::setSubSystem(SubSystem ss)
{
    m_sub = ss;
}

SubSystem Devices::getSubSystem()
{
    return m_sub;
}

void Devices::setSelected(bool s)
{
    selected = s;
}

bool Devices::isSelected() const
{
    return selected;
}

void Devices::setCatched(bool c)
{
    catched = c;
}

bool Devices::isCatched()
{
    return catched;
}

void Devices::setRemoved(bool rem)
{
    removed = rem;
}

bool Devices::isRemoved()
{
    return removed;
}

void Devices::setNotifierId(int num)
{
    notifier_id = num;
}

int Devices::getNotifierId() const
{
    return notifier_id;
}

void Devices::moveTo(const QPoint &to)
{
    if(m_type == TypeObject::PLUGGABLE_TO485){
    m_basept.setX(to.x() - GUI_Constants::CTRL_WIDTH / 2);
    m_basept.setY(to.y() - GUI_Constants::CTRL_HEIGHT / 2);
    }
    else if(m_type == TypeObject::PLUGGABLE_TO2WIRE){
        m_basept.setX(to.x() - GUI_Constants::SENS_RADIUS / 2);
        m_basept.setY(to.y() - GUI_Constants::SENS_RADIUS / 2);
    }
}

QString Devices::getText() const
{
    return m_text;
}

void Devices::setText(QString &txt)
{
    m_text = txt;
}

void Devices::setMasterLineNum(int num)
{
    masterline_num = num;
}

int Devices::getMasterLineNum() const
{
    return masterline_num;
}

TypeObject Devices::getType() const
{
    return m_type;
}

void Devices::setType(TypeObject type)
{
    m_type = type;
}

void Devices::setType(const char *type)
{
    if(type == const_cast<char*>( "SmartDevice")){
        m_type = TypeObject::PLUGGABLE_TO485;
    }
    if(type == const_cast<char*>("Sensor")){
        m_type = TypeObject::PLUGGABLE_TO2WIRE;
    }
    if(type == const_cast<char*>("No_Dev")){
        m_type = TypeObject::NO_DEV;
    }
}
