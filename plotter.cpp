#include "plotter.h"
#include "devicemanager.h"
#include <QPainter>
#include <QListIterator>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>

Plotter::Plotter(ClickableLabel *owner) : m_owner(owner)
{

}

Plotter::~Plotter()
{

}

void Plotter::plotDevice()
{
    QPainter painter;

    QPoint point = m_owner->getMousePosition();

    painter.begin(m_owner);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));


    switch (m_type) {
    case PLUGGABLE_TO485:
    {
        painter.drawRect(point.x() - GUI_Constants::CTRL_WIDTH / 2, point.y() - GUI_Constants::CTRL_HEIGHT / 2, GUI_Constants::CTRL_WIDTH, GUI_Constants::CTRL_HEIGHT);
        break;
    }
    case PLUGGABLE_TO2WIRE:
    {
        painter.drawEllipse(point.x() - GUI_Constants::SENS_RADIUS / 2, point.y() - GUI_Constants::SENS_RADIUS / 2, GUI_Constants::SENS_RADIUS,GUI_Constants::SENS_RADIUS);
        break;
    }
    default:
        break;
    }

    painter.end();
}

void Plotter::plotDevice(Devices *dev)
{
    TypeObject type = dev->getType();
    QColor color;
    QString str_num;
    QString str_model;
    str_model = dev->getModel();
    QFont font("Courier", 8, QFont::DemiBold);
    QFontMetrics fm(font);

    switch (dev->getSubSystem()) {
    case SubSystem::FIRE:
        color = Qt::red;
        break;
    case SubSystem::SKUD:
        color = Qt::blue;
        break;
    case SubSystem::NO_SUBSYSTEM:
        color = Qt::black;
        break;
    default:
        break;
    }

    QPainter painter;
    painter.begin(m_owner);

    painter.setPen(QPen(color, 1, Qt::SolidLine, Qt::FlatCap));


    switch (type) {
    case PLUGGABLE_TO485:
    {
        painter.drawRect(dev->getStartXpt(), dev->getStartYpt(), GUI_Constants::CTRL_WIDTH, GUI_Constants::CTRL_HEIGHT);
        break;
    }

    case PLUGGABLE_TO2WIRE:
    {
        painter.drawEllipse(dev->getStartXpt(),dev->getStartYpt(),GUI_Constants::SENS_RADIUS, GUI_Constants::SENS_RADIUS);
        break;
    }
    case LINE:{
        break;
    }
    default:
        break;
    }
    ///----------добавляем текст с номером устройства
    if(dev->getType() == TypeObject::PLUGGABLE_TO485){
        str_num = QString::number(dev->getNotifierId()) + "_" + QString::number( dev->getUserId());
        painter.setFont(font);
        painter.drawText(dev->getCenter().x() + GUI_Constants::CTRL_WIDTH, dev->getCenter().y() + GUI_Constants::CTRL_HEIGHT, str_num);
    }
    else if(dev->getType() == TypeObject::PLUGGABLE_TO2WIRE){
        str_num = QString::number(dev->getMasterLineNum()) + "_" + QString::number(dev->getNotifierId()) + "_" + QString::number( dev->getUserId());
        painter.setFont(font);
        painter.drawText(dev->getCenter().x() + GUI_Constants::SENS_RADIUS, dev->getCenter().y() + GUI_Constants::SENS_RADIUS, str_num);
    }


    ///--------добавляем текст с моделью устройства
    int textWidth = fm.width(str_model);
    painter.drawText(dev->getCenter().x() - textWidth / 2, dev->getCenter().y(), str_model);
    /// ---------------------------------------------
    painter.end();
}



void Plotter::plotDevice(Devices *dev, QColor &color, int thickness)
{
    TypeObject type = dev->getType();

    QPainter painter;
    painter.begin(m_owner);

    painter.setPen(QPen(color, thickness, Qt::SolidLine, Qt::FlatCap));


    switch (type) {
    case PLUGGABLE_TO485:
    {
        painter.drawRect(dev->getStartXpt(), dev->getStartYpt(), GUI_Constants::CTRL_WIDTH, GUI_Constants::CTRL_HEIGHT);
        break;
    }

    case PLUGGABLE_TO2WIRE:
    {
        painter.drawEllipse(dev->getStartXpt(),dev->getStartYpt(),GUI_Constants::SENS_RADIUS, GUI_Constants::SENS_RADIUS);
        break;
    }
    case LINE:{
        break;
    }
    default:
        break;
    }

    painter.end();
}


void Plotter::plotScheme()
{
    auto &manager = DeviceManager::instance();
    QPainter painter;
    painter.begin(m_owner);

    QListIterator<Devices*> it(manager.getDevices());
    if(!manager.getDevices().isEmpty()){
        while(it.hasNext()){
            Devices * dev = it.next();
            if(!dev->isRemoved())
                plotDevice(dev);
        }
    }

    QListIterator<ConnectionLine*> itl(manager.getLines());
    if(!manager.getLines().isEmpty()){
        while (itl.hasNext()) {
            ConnectionLine * line = itl.next();
            if(!line->isRemoved()){
            plotLine(line);
            }
        }
    }

    painter.end();


}

void Plotter::plotLine(QPoint pt1, QPoint pt2)
{
    QPainter painter;
    painter.begin(m_owner);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(pt1, pt2);
    painter.end();
}

void Plotter::plotLine(QPoint pt1, QPoint pt2, LineRole role)
{
    int fat = 0;
    switch (role) {
    case LineRole::RS485LINE:
        fat = 3;
        break;
    case LineRole::DUALWIRELINE:
        fat = 1;
        break;
    default:
        break;
    }
    QPainter painter;
    painter.begin(m_owner);
    painter.setPen(QPen(Qt::black, fat, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(pt1, pt2);
    painter.end();
}

void Plotter::plotLine(QPoint pt1, QPoint pt2, LineRole role, SubSystem ss)
{
    int fat = 0;
    QColor color;

    switch (role) {
    case LineRole::RS485LINE:
        fat = 3;
        break;
    case LineRole::DUALWIRELINE:
        fat = 1;
        break;
    default:
        break;
    }

    switch (ss) {
    case SubSystem::FIRE:
        color = Qt::red;
        break;
    case SubSystem::SKUD:
        color = Qt::blue;
        break;
    case SubSystem::NO_SUBSYSTEM:
        color = Qt::black;
        break;
    default:
        break;
    }
    QPainter painter;
    painter.begin(m_owner);
    painter.setPen(QPen(color, fat, Qt::SolidLine, Qt::FlatCap));
    painter.drawLine(pt1, pt2);
    painter.end();
}

void Plotter::plotLine(ConnectionLine *line)
{
    static int cnt;
    QPoint lpt;
    QListIterator<QPoint> itp(line->getKeyPointsList());
    if(!line->getKeyPointsList().isEmpty()){
        while (itp.hasNext()) {
            QPoint  point = itp.next();
            if(cnt == 0){
                lpt = m_owner->getMousePosition();
            }
            if(cnt!=0)
            {
            plotLine(lpt,point, line->getRole(),line->getSubSystem());
            }
            cnt++;
            lpt = point;
        }
    }
    cnt = 0;
}


void Plotter::setType(TypeObject type)
{
    m_type = type;
}
