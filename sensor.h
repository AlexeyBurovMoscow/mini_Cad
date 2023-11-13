#ifndef SENSOR_H
#define SENSOR_H

#include "devices.h"
#include <QPoint>
#include <typeinfo>
#include "clickablelabel.h"
#include "utils.h"

class Sensor : public Devices{
    Limits lim;
    QString m_model;
    int radius = GUI_Constants::SENS_RADIUS;

public:
    Sensor(const QPoint& basept);
    ~Sensor(){}

    virtual QString getModel() = 0;

    void checkLimits(QPoint &pt) override;
    void rebuild() override;
    QPoint getCenter() override;



};
#endif // SENSOR_H
