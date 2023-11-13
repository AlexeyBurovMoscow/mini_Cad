#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QDebug>
#include <QLineEdit>
#include "utils.h"

class GUI;
class SetupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetupWidget(GUI * gui, QWidget * parent = 0);
    ~SetupWidget();
private:
    GUI* gui_owner = nullptr;
    QLabel * label = nullptr;
    QLineEdit * edit = nullptr;
    QPushButton * button = nullptr;
    QVBoxLayout * layout = nullptr;

    int line_id = 0;
    int dev_id = 0;
    TypeObject m_type;

public:
    void setText(QString str);
    void setType(TypeObject type);
    void setActualLineId(int id);
    void setActualDevId(int id);

private slots:
    void onOk();
};

#endif // SETUPWIDGET_H
