#include <QAction>
#include "multitabwgt.h"

MultiTabWgt::MultiTabWgt(QWidget *parent): QWidget(parent)
{
    mwgt_wgt_mainlayout = new QVBoxLayout();

    tab = new QTabWidget();
    tab->resize(360,100);

    //linesWgt = new LinesTabWgt(tab);
    fireWgt = new FireTabWgt(tab);
    skudWgt = new SkudTabWgt(tab);

    //tab->addTab(linesWgt,"Lines");//только передать в метод AddTab тип виджета, который надо встроить
    tab->addTab(fireWgt,"FIRE");
    tab->addTab(skudWgt,"SKUD");
    mwgt_wgt_mainlayout->addWidget(tab);
    this->setLayout(mwgt_wgt_mainlayout);

}

MultiTabWgt::~MultiTabWgt()
{}


//LinesTabWgt* MultiTabWgt::getLinesTab() const
//{
//    return linesWgt;
//}

FireTabWgt *MultiTabWgt::getFireTab() const
{
    return fireWgt;
}

SkudTabWgt *MultiTabWgt::getSkudTab() const
{
    return skudWgt;
}

QTabWidget *MultiTabWgt::getTab() const
{
    return tab;
}
