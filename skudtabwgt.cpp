#include "skudtabwgt.h"

SkudTabWgt::SkudTabWgt(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout();         ///не забывать добавлять в вектор кнопки, появляющиеся в процессе
    devGroup = new QGroupBox(tr("devices"));
    sensGroup = new QGroupBox(tr("sensors"));
    devGridLay = new QGridLayout();
    sensGridLay = new QGridLayout();
    bn_s2000 = new QPushButton("S2000");
    bn_s2000->setCheckable(true);
    v_bn.push_back(bn_s2000);
    bn_s2000m = new QPushButton("S2000M");
    bn_s2000m->setCheckable(true);
    v_bn.push_back(bn_s2000m);
    bn_s2000KS = new QPushButton("S2000KS");
    bn_s2000KS->setCheckable(true);
    v_bn.push_back(bn_s2000KS);
    bn_s2000BI = new QPushButton("S2000BI");
    bn_s2000BI->setCheckable(true);
    v_bn.push_back(bn_s2000BI);
    bn_s2000BKI = new QPushButton("S2000BKI");
    bn_s2000BKI->setCheckable(true);
    v_bn.push_back(bn_s2000BKI);
    bn_s2000K = new QPushButton("S2000K");
    bn_s2000K->setCheckable(true);
    v_bn.push_back(bn_s2000K);
    bn_s2000SP1 = new QPushButton("S2000SP1");
    bn_s2000SP1->setCheckable(true);
    v_bn.push_back(bn_s2000SP1);
    bn_s2000_4 = new QPushButton("S2000_4");
    bn_s2000_4->setCheckable(true);
    v_bn.push_back(bn_s2000_4);
    bn_foton = new QPushButton("Foton-4") ;
    bn_foton->setCheckable(true);
    v_bn.push_back(bn_foton);

    bn_FotonShEx = new QPushButton("Foton-ShEx");
    bn_FotonShEx->setCheckable(true);
    v_bn.push_back(bn_FotonShEx);

    bn_StekloEx = new QPushButton("StekloEx");
    bn_StekloEx->setCheckable(true);
    v_bn.push_back(bn_StekloEx);

    bn_ShoroxEx = new QPushButton("ShoroxEx");
    bn_ShoroxEx->setCheckable(true);
    v_bn.push_back(bn_ShoroxEx);

    bn_MkEx = new QPushButton("MkEx");
    bn_MkEx->setCheckable(true);
    v_bn.push_back(bn_MkEx);

    bn_STZex = new QPushButton("STZex");
    bn_STZex->setCheckable(true);
    v_bn.push_back(bn_STZex);

    bn_IPDex = new QPushButton("IPDex");
    bn_IPDex->setCheckable(true);
    v_bn.push_back(bn_STZex);

    bn_IPDLex = new QPushButton("IPDLex");
    bn_IPDLex->setCheckable(true);
    v_bn.push_back(bn_IPDLex);

    bn_IPPex = new QPushButton("IPPex");
    bn_IPPex->setCheckable(true);
    v_bn.push_back(bn_IPPex);

    bn_IPRex = new QPushButton("IPRex");
    bn_IPRex->setCheckable(true);
    v_bn.push_back(bn_IPRex);

    mainLayout->addWidget(createDevsGroup());
    mainLayout->addWidget(createSensGroup());
    this->setLayout(mainLayout);
}

SkudTabWgt::~SkudTabWgt()
{

}

QGroupBox *SkudTabWgt::createSensGroup()
{
    sensGridLay->addWidget(bn_foton,0,0);
    sensGridLay->addWidget(bn_FotonShEx, 0, 1);
    sensGridLay->addWidget(bn_StekloEx, 0, 2);
    sensGridLay->addWidget(bn_ShoroxEx, 0, 3);
    sensGridLay->addWidget(bn_MkEx, 1, 0);
    sensGridLay->addWidget(bn_STZex, 1, 1);
    sensGridLay->addWidget(bn_IPDex, 1, 2);
    sensGridLay->addWidget(bn_IPDLex, 1, 3);
    sensGridLay->addWidget(bn_IPPex, 2, 0);
    sensGridLay->addWidget(bn_IPRex, 2, 1);
    sensGroup->setLayout(sensGridLay);
    return sensGroup;
}

QGroupBox *SkudTabWgt::createDevsGroup()
{
    devGridLay->addWidget(bn_s2000,0,0);
    devGridLay->addWidget(bn_s2000m, 0, 1);
    devGridLay->addWidget(bn_s2000KS, 0, 2);
    devGridLay->addWidget(bn_s2000BI, 0, 3);
    devGridLay->addWidget(bn_s2000BKI, 1, 0);
    devGridLay->addWidget(bn_s2000K, 1, 1);
    devGridLay->addWidget(bn_s2000SP1, 1, 2);
    devGridLay->addWidget(bn_s2000_4, 1, 3);
    devGroup->setLayout(devGridLay);
    return devGroup;
}

QPushButton *SkudTabWgt::get_bnS2000() const
{
    return bn_s2000;
}

QPushButton *SkudTabWgt::get_Foton() const
{
    return bn_foton;
}

QPushButton *SkudTabWgt::get_bnS2000M() const
{
    return bn_s2000m;
}

QPushButton *SkudTabWgt::get_bnS2000KS() const
{
    return bn_s2000KS;
}

QPushButton *SkudTabWgt::get_bnS2000BI() const
{
    return bn_s2000BI;
}

QPushButton *SkudTabWgt::get_bnS2000BKI() const
{
    return bn_s2000BKI;
}

QPushButton *SkudTabWgt::get_bnS2000K() const
{
    return bn_s2000K;
}

QPushButton *SkudTabWgt::get_bnS2000SP1() const
{
    return bn_s2000SP1;
}

QPushButton *SkudTabWgt::get_bnS2000_4() const
{
    return bn_s2000_4;
}

QPushButton *SkudTabWgt::get_bn_FotonShEx() const
{
    return bn_FotonShEx;
}

QPushButton *SkudTabWgt::get_bn_StekloEx() const
{
    return bn_StekloEx;
}

QPushButton *SkudTabWgt::get_bn_ShoroxEx() const
{
    return bn_ShoroxEx;
}

QPushButton *SkudTabWgt::get_bn_MkEx() const
{
    return bn_MkEx;
}

QPushButton *SkudTabWgt::get_bn_STZex() const
{
    return bn_STZex;
}

QPushButton *SkudTabWgt::get_bn_IPDex() const
{
    return bn_IPDex;
}

QPushButton *SkudTabWgt::get_bn_IPDLex() const
{
    return bn_IPDLex;
}

QPushButton *SkudTabWgt::get_bn_IPPex() const
{
    return bn_IPPex;
}

QPushButton *SkudTabWgt::get_bn_IPRex() const
{
    return bn_IPRex;
}

void SkudTabWgt::setCheckedAllBns(bool checked)
{
    foreach (QPushButton* bn, v_bn) {
        bn->setChecked(checked);
    }
}

void SkudTabWgt::setEnabledAllBns(bool enabled)
{
    foreach (QPushButton* bn, v_bn) {
        bn->setEnabled(enabled);
    }
}

void SkudTabWgt::disableExcept(QString str)
{
    if (str == "S2000")
    {
        bn_s2000->setChecked(true);
        bn_foton->setChecked(false);
        bn_s2000m->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);   
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);

    }
    if(str == "foton"){
        bn_s2000->setChecked(false);
        bn_foton->setChecked(true);
        bn_s2000m->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "S2000M")
    {
        bn_s2000m->setChecked(true);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "S2000KS")
    {
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(true);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "S2000BI")
    {
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(true);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "S2000BKI"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(true);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "S20004"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(true);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "S2000K"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(true);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "S2000SP1"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(true);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "FotonShEx"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(true);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "StekloEx"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(true);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "ShoroxEx"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(true);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "MkEx"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(true);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "STZex"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(true);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "IPDex"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(true);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "IPDLex"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(true);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(false);
    }
    if(str == "IPPex"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(true);
        bn_IPRex->setChecked(false);
    }
    if(str == "IPRex"){
        bn_s2000m->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000->setChecked(false);
        bn_s2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_foton->setChecked(false);
        bn_FotonShEx->setChecked(false);
        bn_StekloEx->setChecked(false);
        bn_ShoroxEx->setChecked(false);
        bn_MkEx->setChecked(false);
        bn_STZex->setChecked(false);
        bn_IPDex->setChecked(false);
        bn_IPDLex->setChecked(false);
        bn_IPPex->setChecked(false);
        bn_IPRex->setChecked(true);
    }

}
