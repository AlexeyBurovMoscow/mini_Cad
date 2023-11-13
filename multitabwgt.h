#ifndef COMMONTABWGT_H
#define COMMONTABWGT_H

#include <QWidget>
#include <QTabWidget>
#include "linestabwgt.h"
#include "firetabwgt.h"
#include "skudtabwgt.h"

class MultiTabWgt : public QWidget
{
    Q_OBJECT
public:
    explicit  MultiTabWgt(QWidget *parent = 0);
    ~MultiTabWgt();

private:

    QVBoxLayout * mwgt_wgt_mainlayout = nullptr;
    QTabWidget * tab = nullptr;

    //LinesTabWgt* linesWgt = nullptr;
    FireTabWgt * fireWgt = nullptr;
    SkudTabWgt * skudWgt = nullptr;

public:
    //LinesTabWgt *getLinesTab() const;
    FireTabWgt *getFireTab() const;
    SkudTabWgt *getSkudTab() const;
    QTabWidget *getTab() const;

};

#endif // COMMONTABWGT_H
