#include "linestabwgt.h"
#include <QDebug>

LinesTabWgt::LinesTabWgt(QWidget *parent): QWidget(parent)
{
    groupbox = new QGroupBox();
    groupLayout = new QVBoxLayout();
    mainlayout = new QVBoxLayout();
    row1 = new QHBoxLayout();
    row2 = new QHBoxLayout();
    bnBigLine = new QPushButton("rs485 line");
    v_bn.push_back(bnBigLine);
    label1 = new QLabel("1");
    bnSmallLine = new QPushButton("dual-wire line");
    v_bn.push_back(bnSmallLine);
    label2 = new QLabel("2");
    bnBigLine->setCheckable(true);
    bnSmallLine->setCheckable(true);
    mainlayout->addWidget(createGroup());
    this->setLayout(mainlayout);
}

LinesTabWgt::~LinesTabWgt()
{}

QGroupBox *LinesTabWgt::createGroup()
{
    row1->addWidget(bnBigLine);
    row1->addWidget(label1);
    row2->addWidget(bnSmallLine);
    row2->addWidget(label2);
    groupLayout->addLayout(row1);
    groupLayout->addLayout(row2);
    groupbox->setLayout(groupLayout);
    return groupbox;
}

QPushButton *LinesTabWgt::getBigLineBn() const
{
    return bnBigLine;
}

QPushButton *LinesTabWgt::getSmallLineBn() const
{
    return bnSmallLine;
}

void LinesTabWgt::setCheckedAllBns(bool checked)
{
    foreach (QPushButton* bn, v_bn) {
        bn->setChecked(checked);
    }
}

void LinesTabWgt::setEnabledAllBns(bool enabled)
{
    foreach (QPushButton* bn, v_bn) {
        bn->setEnabled(enabled);
    }
}

