#include "smartdevice.h"
#include <QDebug>



SmartDevice::SmartDevice(const QPoint &basept):
    Devices(m_owner, basept)
{
    m_basept.setX(m_basept.x() - GUI_Constants::CTRL_WIDTH / 2);
    m_basept.setY(m_basept.y() - GUI_Constants::CTRL_HEIGHT / 2);
    lim.topLeft = {m_basept.x(), m_basept.y()};
    lim.topRight = {m_basept.x() + width, m_basept.y()};
    lim.downLeft = {m_basept.x(), m_basept.y() + height};
    lim.downRight = {m_basept.x() + width, m_basept.y() + height};
}


void SmartDevice::checkLimits(QPoint &pt)
{
    if ((lim.topLeft.x() < pt.x()) && (pt.x() < lim.topRight.x()) &&
            (lim.topLeft.y() < pt.y())  && (pt.y() < lim.downLeft.y()))

    {
        setSelected(true);
    }
    else
    {
        setSelected(false);
    }
}

void SmartDevice::rebuild()
{
    lim.topLeft = {m_basept.x(), m_basept.y()};
    lim.topRight = {m_basept.x() + width, m_basept.y()};
    lim.downLeft = {m_basept.x(), m_basept.y() + height};
    lim.downRight = {m_basept.x() + width, m_basept.y() + height};
}

QPoint SmartDevice::getCenter()
{
    int center_x = lim.topLeft.x() + (lim.topRight.x() - lim.topLeft.x()) / 2;
    int center_y = lim.topLeft.y() + (lim.downLeft.y() - lim.topLeft.y()) / 2;
    QPoint pt =  QPoint{center_x,center_y};
    return pt;
}

