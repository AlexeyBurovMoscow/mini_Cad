#include "setupwidget.h"
#include "devicemanager.h"

SetupWidget::SetupWidget(GUI *gui, QWidget *parent) : QWidget(parent)
{
    gui_owner = gui;
    label = new QLabel("Settings");
    edit = new QLineEdit("Number:");
    button = new QPushButton("Ok");
    layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->addWidget(label);
    layout->addWidget(edit);
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, this, &SetupWidget::onOk);
}

SetupWidget::~SetupWidget()
{

}

void SetupWidget::setText(QString str)
{
    edit->setText(str);
}

void SetupWidget::setType(TypeObject type)
{
    m_type = type;
}

void SetupWidget::setActualLineId(int id)
{
    line_id = id;
}

void SetupWidget::setActualDevId(int id)
{
    dev_id = id;
}

void SetupWidget::onOk()
{
    auto manager = DeviceManager::instance();
    switch (m_type) {
    case PLUGGABLE_TO485:{
        manager.getDevices().at(dev_id)->setUserId(edit->text().toInt());
        break;}
    case PLUGGABLE_TO2WIRE:{
        manager.getDevices().at(dev_id)->setUserId(edit->text().toInt());
        break;}
    case LINE:{
        manager.getLines().at(line_id)->setUserId(edit->text().toInt());
        manager.getLines().at(line_id)->notifyAll();
        break;}
    default:{
        break;}
    }
    this->hide();
}
