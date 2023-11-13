#include <QMouseEvent>
#include <QAction>
#include <QColor>
#include <QString>
#include <QMessageBox>
#include "clickablelabel.h"
#include "gui.h"
#include "devicemanager.h"
#include "devices.h"
#include "smartdevice.h"
#include "sensor.h"
#include "connectionline.h"
#include "setupwidget.h"
#include <QDebug>

ClickableLabel::ClickableLabel(GUI *gui, QWidget *parent):  QLabel(parent)
{
    counter = 0;
    gui_owner = gui;
    qpm = new QPixmap();
    this->startTimer(30);
    this->setMouseTracking(true);       //координатное сопровождение курсора мыши
    plotter = new Plotter(this);
    setMode(Mode::DRAW);
    connectMenu();
}

ClickableLabel::ClickableLabel(GUI *gui, const QString &text, QWidget *parent): QLabel(text, parent)
{
    counter = 0;
    gui_owner = gui;
    qpm = new QPixmap();
    this->startTimer(40);
    this->setMouseTracking(true);
    plotter = new Plotter(this);
    setMode(Mode::DRAW);
    connectMenu();

}


ClickableLabel::~ClickableLabel()
{
    delete qpm;
    delete screen;
}


void ClickableLabel::mouseMoveEvent(QMouseEvent *ev)
{
    auto manager = DeviceManager::instance();
    cursor_x = ev->pos().x();
    cursor_y = ev->pos().y();
    QPoint pt =  QPoint(cursor_x, cursor_y);
    gui_owner->showMousePosition(pt);

    QListIterator<Devices*> it(manager.getDevices());
    if(!manager.getDevices().isEmpty()){
        while(it.hasNext()){
            Devices* dev = it.next();
            dev->checkLimits(pt);
            if((dev->isSelected()) &&(!dev->isRemoved()) && (gui_owner->getTypeObject() != TypeObject::LINE)) {
                this->setType(typeid(*dev).name());
            }
        }
    }

    QListIterator<ConnectionLine*> itl(manager.getLines());
    if(!manager.getLines().isEmpty()){
        while(itl.hasNext()){
            ConnectionLine* line = itl.next();
            if(!line->isRemoved()){
            line->checkLimits(pt);
            }
        }
    }
}


void ClickableLabel::mousePressEvent(QMouseEvent *ev){

    ConnectionLine * line = nullptr;

    auto &manager = DeviceManager::instance();
    setDevCnt();


    if(mode == Mode::DRAW){
        if(ev->button() == Qt::LeftButton){
            ///в этот список должны быть занесены все кнопки, отвечающие за размещение устройств линии RS485 во вкладках Fire и Scud
            if((getType() == TypeObject::PLUGGABLE_TO485)&&(
                        gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnKDL()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000M()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000m()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000KS()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000ks()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000BI()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000bi()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000BKI()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000BKI()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000K()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000K()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000SP1()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000SP1()->isChecked()
                        || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000_4()->isChecked()
                        || gui_owner->getMultiTabWgt()->getSkudTab()->get_bnS2000_4()->isChecked())
                    ){
                setClickCnt(0);
                SmartDevice* smart_dev = dynamic_cast<SmartDevice*>(manager.makeItem(getMousePosition()));
                smart_dev->setType(gui_owner->getTypeObject());
                smart_dev->setId(getDevCnt());
                smart_dev->setSubSystem(gui_owner->getSubSystem());
                manager.addDevice(smart_dev);

                incrDevCnt();
            }           ///в этот список должны быть занесены все кнопки, отвечающие за размещение устройств линии dual-wire во вкладках Fire и Scud
            if((getType() == TypeObject::PLUGGABLE_TO2WIRE)&&(gui_owner->getMultiTabWgt()->getFireTab()->get_bnDIP34()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_Foton()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_FotonShEx()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_StekloEx()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_ShoroxEx()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_MkEx()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_STZex()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_IPDex()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_IPDLex()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_IPPex()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getSkudTab()->get_bn_IPRex()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS2000_IP02()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnIPR513_3A()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS_2000_IK()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS_2000_PIK()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS_2000_SHIK()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS_2000_V()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS_2000_ST()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS_2000_SMK()->isChecked()
                                                   || gui_owner->getMultiTabWgt()->getFireTab()->get_bnS_2000_KT() )
                    ){
                setClickCnt(0);
                Sensor* sens_dev = dynamic_cast<Sensor*>(manager.makeItem(getMousePosition()));
                sens_dev->setType(gui_owner->getTypeObject());
                sens_dev->setId(getDevCnt());
                sens_dev->setSubSystem(gui_owner->getSubSystem());
                manager.addDevice(sens_dev);
                incrDevCnt();
            }
            if((getType() == TypeObject::LINE) && (isLineProcess())){
                if(ev->button() == Qt::RightButton){

                }
                ///------если файл не подгружался из json-------
                if(!gui_owner->isJSONloaded()){
                    if(getClickCnt() == 0)  {
                        this->setActualLineNumber(getLineCnt());
                        line = new ConnectionLine();
                        line->setId(getLineCnt());
                        line->setUserId(getLineCnt());
                        manager.addConnectionLine(line);
                        incrLineCnt();
                    }


                    line =  manager.getConnectionLine(getLineCnt()-1);

                    if((line != nullptr) && (!isLineLocked())){
                        line->addKeyPoint(point);
                        if(gui_owner->getRole() == LineRole::RS485LINE){
                            line->setRole(LineRole::RS485LINE);
                        }
                        else if(gui_owner->getRole() == LineRole::DUALWIRELINE){
                            line->setRole(LineRole::DUALWIRELINE);
                        }

                        if(gui_owner->getSubSystem() == SubSystem::FIRE){
                            line->setSubSystem(SubSystem::FIRE);
                        }
                        else if(gui_owner->getSubSystem() == SubSystem::SKUD){
                            line->setSubSystem(SubSystem::SKUD);
                        }
                        ///-------
                        ///если устройство выделено и щелкнуто - добавить его в список устройств линии
                        QListIterator<Devices*> it(manager.getDevices());
                        if(!manager.getDevices().isEmpty()){
                            while(it.hasNext()){
                                Devices* dev = it.next();
                                if((dev->isSelected()) &&(!dev->isRemoved())){
                                    qDebug() << "dev cliccked type = " << dev->getType();
                                    point = dev->getCenter();
                                    if(line->getSubscribers().isEmpty()){
                                        if(gui_owner->getSubSystem() == dev->getSubSystem() )
                                        {
                                            line->setSubSystem(dev->getSubSystem());
                                            line->addSubscriber(dev);
                                        }
                                        else{
                                            QMessageBox msg;
                                            msg.setText("Недопустимое действие!");
                                            msg.exec();
                                            return;
                                        }
                                    }
                                    else{
                                        if(line->getSubSystem() == dev->getSubSystem()){
                                            line->addSubscriber(dev);
                                        }
                                        else{
                                            manager.removeLastLine();
                                            decrLineCnt();
                                            this->setType(TypeObject::NO_DEV);
                                            //gui_owner->getMultiTabWgt()->getLinesTab()->setCheckedAllBns(false);
                                            QMessageBox msg;
                                            msg.setText("Недопустимое действие!");
                                            msg.exec();
                                            return;
                                        }
                                    }


                                    if((dynamic_cast<SmartDevice*>(dev)) && (line->getRole() == LineRole::RS485LINE)){
                                        dev->setNotifierId(line->getId());
                                    }
                                    if((dynamic_cast<SmartDevice*>(dev)) && (line->getRole() == LineRole::DUALWIRELINE)){
                                        line->setMasterLineNum(dev->getNotifierId());
                                    }

                                    if((dynamic_cast<Sensor*>(dev)) && (line->getRole() == LineRole::DUALWIRELINE)){
                                        dev->setNotifierId(line->getId());
                                        dev->setMasterLineNum(line->getMasterLineNum());
                                    }
                                    if((dynamic_cast<Sensor*>(dev)) && (line->getRole() == LineRole::RS485LINE)){
                                        manager.removeLastLine();
                                        decrLineCnt();
                                        this->setType(TypeObject::NO_DEV);
                                        //gui_owner->getMultiTabWgt()->getLinesTab()->setCheckedAllBns(false);
                                        QMessageBox msg;
                                        msg.setText("Недопустимое действие!");
                                        msg.exec();
                                        return;
                                    }
                                }
                                point = getMousePosition();
                            }
                        }
                        /// ------
                        incrementClickCnt();
                    }

                }   ///-------------если файл подгружен из json--------------
                else if(gui_owner->isJSONloaded()){
                    setLineCount(manager.getLines().length());
                    line = new ConnectionLine();
                    line->setId(manager.getLines().length());
                    manager.addConnectionLine(line);
                    this->setActualLineNumber(getLineCnt());
                    point = getMousePosition();
                    line->addKeyPoint(point);
                    ///-------отследить клик на устройстве-------
                    QListIterator<Devices*> it(manager.getDevices());
                    if(!manager.getDevices().isEmpty()){
                        while(it.hasNext()){
                            Devices* dev = it.next();
                            if((dev->isSelected()) &&(!dev->isRemoved())){
                                line->addSubscriber(dev);
                                dev->setNotifierId(line->getId());
                            }
                        }
                    }
                    /// -----------------------------------------
                    incrementClickCnt();
                    gui_owner->setJSONloaded(false);
                    incrLineCnt();
                }

            }
        }
    }
    if(mode == Mode::CORRECT){
        if(ev->button() == Qt::RightButton){
            auto res = std::find_if(manager.getLines().begin(), manager.getLines().end(), [](ConnectionLine * line){
                    if(!line->isRemoved()){
                    return line->isSelected();
        }
                    else return false;
        });

            if(res != manager.getLines().end()){
                line_finded = true;
            }
            else{
                line_finded = false;
            }

            auto result = std::find_if(manager.getDevices().begin(), manager.getDevices().end(), [](Devices  *dev){
                    if(!dev->isRemoved())
            {
                    return dev->isSelected();
        }
                    else return false;
        });
            if(result != manager.getDevices().end()){
                dev_finded = true;
            }
            else{
                dev_finded = false;
            }

            if(dev_finded || line_finded){
                enableMenu();
            }
            else{
                disableMenu();
            }
        }
        if(ev->button() == Qt::LeftButton){
            QListIterator<Devices*> it(manager.getDevices());
            if(!manager.getDevices().isEmpty()){
                while(it.hasNext()){
                    Devices* dev = it.next();
                    if(dev->isCatched()){
                        dev->setCatched(false);
                        dev->moveTo(QPoint(cursor_x, cursor_y));
                        dev->rebuild();
                    }
                    if(dev->isSelected()){
                        plotter->setType(this->getType());
                        dev->setCatched(true);
                    }
                }
            }
        }

    }

}


void ClickableLabel::contextMenuEvent(QContextMenuEvent *event)
{
    if(mode == Mode::CORRECT)
    {
        if(( menu_ctx ) && (isMenuEnabled())) {
            menu_ctx->exec( event->globalPos() );
        }
    }
    if((mode == Mode::DRAW) && (gui_owner->getTypeObject() == TypeObject::LINE) && (isLineProcess())){
        menu_line->exec(event->globalPos());
    }
}

void ClickableLabel::paintEvent(QPaintEvent *evt)
{
    QColor color = Qt::green;
    auto manager = DeviceManager::instance();
    mode = gui_owner->getMode();

    if(mode == Mode::CORRECT){
        highLightDevice(evt);

        QListIterator<Devices*> it(manager.getDevices());
        if(!manager.getDevices().isEmpty()){
            while(it.hasNext()){
                Devices* dev = it.next();
                if(dev->isCatched()){
                    plotter->plotDevice();
                }
            }
        }
    }
    if(mode == Mode::DRAW){
        markPictureRegion(evt);
        point =  QPoint(cursor_x, cursor_y);
        QListIterator<Devices*> it(manager.getDevices());
        if(!manager.getDevices().isEmpty()){
           while(it.hasNext()){
               Devices* dev = it.next();
               dev->checkLimits(point);
               if(dev->isSelected()&&(!dev->isRemoved())){
                   plotter->plotDevice(dev,color,4);
                   point =  dev->getCenter();
               }
           }
        }
        if((m_type == TypeObject::LINE) && (!manager.getLines().isEmpty()) && (!isLineLocked()) && (isLineProcess())  && (getClickCnt() > 0)){
        plotter->plotLine(point, manager.getConnectionLine(getActualLineNumber())->getLastKeyPoint());
        }
    }

    plotter->plotScheme();

}


void ClickableLabel::timerEvent(QTimerEvent *)
{
    if (counter == 10)
       blink = !blink;

    update();
    counter++;
    if (counter>10)
        counter=0;
}

void ClickableLabel::markPictureRegion(QPaintEvent *evt)
{

    TypeObject type;
    type = gui_owner->getTypeObject();
    QLabel::paintEvent(evt);
    QPainter painter(this);
    painter.setPen( QPen( Qt::blue, 3 ) );
    switch (type){
    case PLUGGABLE_TO485:{
        if(blink){
            painter.drawRect(cursor_x - GUI_Constants::CTRL_WIDTH / 2, cursor_y - GUI_Constants::CTRL_HEIGHT / 2, GUI_Constants::CTRL_WIDTH, GUI_Constants::CTRL_HEIGHT);
        }
        break;
    }
    case PLUGGABLE_TO2WIRE:{
        if(blink){
            painter.drawEllipse(cursor_x - GUI_Constants::SENS_RADIUS / 2, cursor_y - GUI_Constants::SENS_RADIUS / 2, GUI_Constants::SENS_RADIUS,GUI_Constants::SENS_RADIUS);
        }
        break;
    }
    case LINE:{
        if(blink){
            QPoint hline_begin{cursor_x - 10, cursor_y};
            QPoint hline_end{cursor_x + 10, cursor_y};
            QPoint vline_begin{cursor_x, cursor_y - 10};
            QPoint vline_end{cursor_x, cursor_y + 10};
            painter.drawLine(hline_begin, hline_end);
            painter.drawLine(vline_begin, vline_end);
        }
        break;
    }
    default:
        break;
    }
    painter.end();
}


void ClickableLabel::highLightDevice(QPaintEvent *evt)
{
    auto &manager = DeviceManager::instance();
    QLabel::paintEvent(evt);
    QPainter painter(this);
    painter.setPen( QPen( Qt::green, 6 ) );

    QListIterator<Devices*> it(manager.getDevices());
    if(!manager.getDevices().isEmpty()){
        while(it.hasNext()){
            Devices * dev = it.next();
            if(dev->isSelected()){
                if(dynamic_cast<SmartDevice*>(dev)){
                    if(!dev->isRemoved())
                    {
                        painter.drawRect(dev->getStartXpt(), dev->getStartYpt(), GUI_Constants::CTRL_WIDTH, GUI_Constants::CTRL_HEIGHT);
                    }
                }
                else if(dynamic_cast<Sensor*>(dev)){
                    if(!dev->isRemoved())
                    {
                        painter.drawEllipse(dev->getStartXpt(), dev->getStartYpt(), GUI_Constants::SENS_RADIUS,GUI_Constants::SENS_RADIUS);
                    }
                }
            }
        }
    }

    QListIterator<ConnectionLine*> itl(manager.getLines());
    if(!manager.getLines().isEmpty()){
        while(itl.hasNext()){
            ConnectionLine * line = itl.next();
            if(line->isSelected()){
                if(!line->isRemoved()){
                    for(int i = 0; i < line->getKeyPointsList().length(); i++){
                        if(i > 0){
                            painter.drawLine(line->getKeyPointsList().at(i), line->getKeyPointsList().at(i-1));
                        }
                    }

                }
            }
        }
    }
    painter.end();
}

void ClickableLabel::connectMenu()
{
    menu_ctx = new QMenu(this);
    QAction * remove_action = menu_ctx->addAction("remove this");
    QAction * setup_action = menu_ctx->addAction("setup this");
    QObject::connect(remove_action, &QAction::triggered, this, &ClickableLabel::onRemoveAction);
    QObject::connect(setup_action, &QAction::triggered, this, &ClickableLabel::onSetupAction);

    menu_line = new QMenu(this);
    QAction * line_end_action = menu_line->addAction("end line");
    QObject::connect(line_end_action, &QAction::triggered, this, &ClickableLabel::onEndLineAction);
}

void ClickableLabel::enableMenu()
{
    if(line_finded || dev_finded){
    cme = true;
    }
}

void ClickableLabel::disableMenu()
{
    cme = false;
}

bool ClickableLabel::isMenuEnabled()
{
    return cme;
}

void ClickableLabel::setClickCnt(int cnt)
{
    click_cnt = cnt;
}

int ClickableLabel::getClickCnt()
{
    return click_cnt;
}

void ClickableLabel::incrementClickCnt()
{
    click_cnt++;
}

void ClickableLabel::lockLine()
{
    le = false;
}

void ClickableLabel::unlockLine()
{
    le = true;
}

bool ClickableLabel::isLineLocked()
{
    return le;
}

void ClickableLabel::finishLine()
{
    line_process = false;
}

void ClickableLabel::setLineInProcess()
{
    line_process = true;
}

bool ClickableLabel::isLineProcess()
{
    return line_process;
}

QPoint ClickableLabel::getMousePosition() const
{
    return QPoint(cursor_x, cursor_y);
}


TypeObject ClickableLabel::getTypeObject() const
{
    return m_type;
}

void ClickableLabel::setMode(Mode m)
{
    mode = m;
}

Mode ClickableLabel::getMode()
{
    return mode;
}

void ClickableLabel::setActualLineNumber(int num)
{
    current_line = num;
}

int ClickableLabel::getActualLineNumber()
{
    return current_line;
}

TypeObject ClickableLabel::getType() const
{
    return m_type;
}

void ClickableLabel::setType(TypeObject type)
{
    m_type = type;
}

void ClickableLabel::setType(const char *type)
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

void ClickableLabel::endLine()
{

}

void ClickableLabel::setLineCount(int val)
{
    line_cnt = val;
}

int ClickableLabel::getLineCnt()
{
    return line_cnt;
}

void ClickableLabel::incrLineCnt()
{
    line_cnt++;
}

void ClickableLabel::decrLineCnt()
{
    line_cnt--;
}

void ClickableLabel::setDevCnt()
{
    //dev_cnt = val;
    auto &manager = DeviceManager::instance();
    dev_cnt = manager.getDevices().length();
    qDebug() << "setDevCnt() = " << dev_cnt;
}

int ClickableLabel::getDevCnt()
{
    qDebug() << "getDevCnt()" << dev_cnt;
    return dev_cnt;
}

void ClickableLabel::incrDevCnt()
{
    //qDebug() << "dev_cnt = " << dev_cnt;
    //dev_cnt++;
    auto &manager = DeviceManager::instance();
    dev_cnt = manager.getDevices().length();
    qDebug() << "dev_cnt = " << dev_cnt;
}


void ClickableLabel::onTypeObjectChanged(TypeObject type)
{
        m_type = type;
}

void ClickableLabel::onRemoveAction()
{
    qDebug() << "onRemoveAction(), m_type = " << m_type;
    auto &manager = DeviceManager::instance();
    if((m_type == TypeObject::PLUGGABLE_TO2WIRE) || (m_type == TypeObject::PLUGGABLE_TO485) || (m_type == TypeObject::ANY_DEV))
    {
        manager.removeDevice();
    }

    manager.removeLine();
    gui_owner->rememTypeObject();


}

void ClickableLabel::onEndLineAction()
{
    auto &manager = DeviceManager::instance();
    m_type = TypeObject::ANY_DEV;
    finishLine();
    lockLine();
    setClickCnt(0);

    //gui_owner->getMultiTabWgt()->getLinesTab()->getBigLineBn()->setChecked(false);
    //gui_owner->getMultiTabWgt()->getLinesTab()->getSmallLineBn()->setChecked(false);
    gui_owner->setType(m_type);
    manager.getConnectionLine(getActualLineNumber())->endLine();
}

void ClickableLabel::onSetupAction()
{
    auto &manager = DeviceManager::instance();
    QListIterator<Devices*> it(manager.getDevices());
    if(!manager.getDevices().isEmpty()){
        while(it.hasNext()){
            Devices * dev = it.next();
            if(dev->isSelected()){
                if(!dev->isRemoved()){
                    QString txt = QString::number(dev->getUserId());
                    gui_owner->getSetupWgt()->setText(txt);
                    gui_owner->getSetupWgt()->setActualDevId(dev->getId());
                    gui_owner->getSetupWgt()->setType(dev->getType());
                }

            }
        }
    }

    QListIterator<ConnectionLine*> itl(manager.getLines());
    if(!manager.getLines().isEmpty()){
        while(itl.hasNext()){
            ConnectionLine * line = itl.next();
            if(line->isSelected()){
                if(!line->isRemoved()){
                    QString txt = QString::number(line->getUserId());
                    gui_owner->getSetupWgt()->setText(txt);
                    gui_owner->getSetupWgt()->setActualLineId(line->getId());
                    gui_owner->getSetupWgt()->setType(TypeObject::LINE);
                }

            }
        }
    }
    gui_owner->getSetupWgt()->show();
}

void ClickableLabel::onMenuCalled()
{
    if(isLineProcess()){
        finishLine();
    }
    //gui_owner->getMultiTabWgt()->getLinesTab()->setCheckedAllBns(false);
    gui_owner->getMultiTabWgt()->getFireTab()->setCheckedAllBns(false);
    gui_owner->getMultiTabWgt()->getSkudTab()->setCheckedAllBns(false);
}


