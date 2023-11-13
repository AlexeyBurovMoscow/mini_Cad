#ifndef SMARTDEVICE_H
#define SMARTDEVICE_H

#include <QPoint>
#include <typeinfo>
#include "devices.h"
#include "clickablelabel.h"
#include "utils.h"

class SmartDevice : public Devices{
    int width = GUI_Constants::CTRL_WIDTH;
    int height = GUI_Constants::CTRL_HEIGHT;
    Limits lim;
    QString m_model;

public:
    SmartDevice(const QPoint& basept);
    ~SmartDevice(){}


    virtual QString getModel() = 0;

    void checkLimits(QPoint &pt) override;
    void rebuild() override;
    QPoint getCenter() override;

};

#endif // SMARTDEVICE_H
