#ifndef DEVICES_H
#define DEVICES_H

#include <QPoint>
#include <QString>
#include <typeinfo>
#include <QDebug>
#include "utils.h"
#include "clickablelabel.h"

class ClickableLabel;

class Devices{
public:
    Devices(ClickableLabel* owner, const QPoint &bp) : m_basept(bp){
        m_owner = owner;
    }
    ~Devices();

private:
    int id = 0;
    int notifier_id = 0;
    TypeObject m_type;
    SubSystem m_sub;
    Models model;
    bool selected = false;
    bool catched = false;
    bool removed = false;
    int width = 0;
    int height = 0;
    int user_id = 0;
    QString m_text = "x_x";
    int masterline_num = 0;

protected:
    ClickableLabel * m_owner = nullptr;
    QPoint m_basept;

    struct Limits{
        QPoint topLeft;
        QPoint topRight;
        QPoint downLeft;
        QPoint downRight;
        int x_axis;
        int y_axis;
    };

public:
    void setUserId(int num);
    int getUserId() const;

    int getStartXpt(){return m_basept.x();}
    int getStartYpt(){return m_basept.y();}

    void setWidth(int w);
    int getWidth() const;

    void setHeight(int h);
    int getHeight() const;

    int getId() const;
    void setId(const int cnt);

    void setSelected(bool s);
    bool isSelected() const;

    void setCatched(bool c);
    bool isCatched();

    void setRemoved(bool rem);
    bool isRemoved();

    void setNotifierId(int num);
    int getNotifierId() const;

    void setSubSystem(SubSystem ss);
    SubSystem getSubSystem();

    void moveTo(const QPoint& to);

    QString getText() const;
    void setText(QString &txt);

    void setMasterLineNum(int num);
    int getMasterLineNum() const;

    TypeObject getType() const;
    void setType(TypeObject type);
    void setType(const char* type);

    virtual QString getModel() = 0;
    virtual void checkLimits(QPoint &pt) = 0;
    virtual void rebuild() = 0;
    virtual QPoint getCenter() = 0;

};

#endif // DEVICES_H
