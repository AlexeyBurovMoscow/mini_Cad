#include "sensor.h"
#include <QDebug>

Sensor::Sensor(const QPoint &basept) : Devices(m_owner, basept)
{
    m_basept.setX(m_basept.x() - GUI_Constants::SENS_RADIUS / 2);
    m_basept.setY(m_basept.y() - GUI_Constants::SENS_RADIUS / 2);
    lim.x_axis = radius;
    lim.y_axis = radius;
}

void Sensor::checkLimits(QPoint &pt)
{
    double cpx; //central point эллипса по оси x
    double cpy; //central point эллипса по оси y
    double dx;  //координата искомой точки по x в пересчете на координаты эллипса
    double dy;  //координата искомой точки по y в пересчете на координаты эллипса
    double f;   //число по которому будем определять в границах эллипса или нет


    cpx = m_basept.x() + radius /2;
    cpy = m_basept.y() + radius /2;
    dx = pt.x() - cpx;
    dy = cpy - pt.y();

    f = ((dx * dx) / (lim.x_axis * lim.x_axis)) + ((dy * dy) / (lim.y_axis * lim.y_axis));

///----------------------------------------------------------
///             тестовый вывод
//    qDebug()<< "checkLimits()----id = " << getId() << "-------------";
//    qDebug() << "center at x = " << cpx << "," << cpy;
//    qDebug() << "size_x = " << lim.x_axis << " size_y = " << lim.y_axis;
//    qDebug() << "f = " << f;
/// ---------------------------------------------------------
    if(f < 1) {
        setSelected(true);

    }
    else{
        setSelected(false);
    }
}

void Sensor::rebuild()
{
    lim.x_axis = radius;
    lim.y_axis = radius;
}

QPoint Sensor::getCenter()
{
    int center_x = m_basept.x() + GUI_Constants::SENS_RADIUS / 2;
    int center_y = m_basept.y() + GUI_Constants::SENS_RADIUS / 2;
    QPoint qp{center_x, center_y};
    return qp;
}

