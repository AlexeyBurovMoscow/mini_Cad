#ifndef PLOTTER_H
#define PLOTTER_H

#include <QColor>
#include "gui.h"
#include "clickablelabel.h"
#include "devices.h"

class ConnectionLine;
class Devices;
class ClickableLabel;
class Plotter
{
    TypeObject m_type;
protected:
    ClickableLabel * m_owner = nullptr;

public:
    Plotter(ClickableLabel * owner);
    ~Plotter();

    void plotDevice();
    void plotDevice(Devices * dev);
    void plotDevice(Devices * dev, QColor &color, int thickness);

    void plotScheme();

    void plotLine(QPoint pt1, QPoint pt2);
    void plotLine(QPoint pt1, QPoint pt2, LineRole role);
    void plotLine(QPoint pt1, QPoint pt2, LineRole role, SubSystem ss);
    void plotLine(ConnectionLine * line);


    void setType(TypeObject type);
};

#endif // PLOTTER_H
