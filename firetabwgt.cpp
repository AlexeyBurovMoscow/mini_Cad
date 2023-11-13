#include "firetabwgt.h"

FireTabWgt::FireTabWgt(QWidget *parent): QWidget(parent)
{
    mainLayout = new QVBoxLayout();
    devGroup = new QGroupBox(tr("RS485 устройства"));
    sensGroup = new QGroupBox(tr("датчики"));
    devGridLay = new QGridLayout();
    sensGridLay = new QGridLayout();
    bn_s2000 = new QPushButton("S2000");
    bn_s2000->setCheckable(true);
    v_bn.push_back(bn_s2000);           ///не забыть добавлять в вектор кнопки, которые будут появляться в процессе
    bn_kdl = new QPushButton("KDL");
    bn_kdl->setCheckable(true);
    v_bn.push_back(bn_kdl);
    bn_s2000m = new QPushButton("S2000M");
    bn_s2000m->setCheckable(true);
    v_bn.push_back(bn_s2000m);
    bn_2000KS = new QPushButton("S2000KS");
    bn_2000KS->setCheckable(true);
    v_bn.push_back(bn_2000KS);
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
    bn_dip34 = new QPushButton("DIP34") ;
    bn_dip34->setCheckable(true);
    v_bn.push_back(bn_dip34);
    ///-------
    bn_S2000_IP02 = new QPushButton("S2000_IP02");
    bn_S2000_IP02->setCheckable(true);
    v_bn.push_back(bn_S2000_IP02);

    bn_IPR513_3A = new QPushButton("IPR513_3A");
    bn_IPR513_3A->setCheckable(true);
    v_bn.push_back(bn_IPR513_3A);

    bn_S_2000_IK = new QPushButton("S2000IK");
    bn_S_2000_IK->setCheckable(true);
    v_bn.push_back(bn_S_2000_IK);

    bn_S_2000_PIK = new QPushButton("S2000PIK");
    bn_S_2000_PIK->setCheckable(true);
    v_bn.push_back(bn_S_2000_PIK);

    bn_S_2000_SHIK = new QPushButton("S2000SHIK");
    bn_S_2000_SHIK->setCheckable(true);
    v_bn.push_back(bn_S_2000_SHIK);

    bn_S_2000_V = new QPushButton("S2000V");
    bn_S_2000_V->setCheckable(true);
    v_bn.push_back(bn_S_2000_V);

    bn_S_2000_ST = new QPushButton("S2000ST");
    bn_S_2000_ST->setCheckable(true);
    v_bn.push_back(bn_S_2000_ST);

    bn_S_2000_SMK = new QPushButton("S2000SMK");
    bn_S_2000_SMK->setCheckable(true);
    v_bn.push_back(bn_S_2000_SMK);

    bn_S_2000_KT = new QPushButton("S2000KT");
    bn_S_2000_KT->setCheckable(true);
    v_bn.push_back(bn_S_2000_KT);
    ///----------
    mainLayout->addWidget(createDevsGroup());
    mainLayout->addWidget(createSensGroup());
    this->setLayout(mainLayout);
}

FireTabWgt::~FireTabWgt()
{}

QGroupBox *FireTabWgt::createSensGroup()
{
    sensGridLay->addWidget(bn_dip34,0,0);
    sensGridLay->addWidget(bn_S2000_IP02, 0, 1);
    sensGridLay->addWidget(bn_IPR513_3A, 0, 2);
    sensGridLay->addWidget(bn_S_2000_IK, 0, 3);
    sensGridLay->addWidget(bn_S_2000_PIK, 1, 0);
    sensGridLay->addWidget(bn_S_2000_SHIK, 1, 1);
    sensGridLay->addWidget(bn_S_2000_V, 1, 2);
    sensGridLay->addWidget(bn_S_2000_ST, 1, 3);
    sensGridLay->addWidget(bn_S_2000_SMK, 2, 0);
    sensGridLay->addWidget(bn_S_2000_KT, 2, 1);
    sensGroup->setLayout(sensGridLay);
    return sensGroup;
}

QGroupBox *FireTabWgt::createDevsGroup()
{
    devGridLay->addWidget(bn_s2000, 0, 0);
    devGridLay->addWidget(bn_s2000m, 0, 1);
    devGridLay->addWidget(bn_2000KS, 0, 2);
    devGridLay->addWidget(bn_s2000BI, 0, 3);
    devGridLay->addWidget(bn_s2000BKI, 1, 0);
    devGridLay->addWidget(bn_s2000K, 1, 1);
    devGridLay->addWidget(bn_s2000SP1, 1, 2);
    devGridLay->addWidget(bn_s2000_4, 1, 3);
    devGridLay->addWidget(bn_kdl, 2, 0);
    devGroup->setLayout(devGridLay);
    return devGroup;
}

QPushButton *FireTabWgt::get_bnS2000() const
{
    return bn_s2000;
}

QPushButton *FireTabWgt::get_bnS2000m() const
{
    return bn_s2000m;
}

QPushButton *FireTabWgt::get_bnS2000ks() const
{
    return bn_2000KS;
}

QPushButton *FireTabWgt::get_bnS2000bi() const
{
    return bn_s2000BI;
}

QPushButton *FireTabWgt::get_bnS2000BKI() const
{
    return bn_s2000BKI;
}

QPushButton *FireTabWgt::get_bnS2000K() const
{
    return bn_s2000K;
}

QPushButton *FireTabWgt::get_bnS2000SP1() const
{
    return bn_s2000SP1;
}

QPushButton *FireTabWgt::get_bnS2000_4() const
{
    return bn_s2000_4;
}

QPushButton *FireTabWgt::get_bnKDL() const
{
    return bn_kdl;
}

QPushButton *FireTabWgt::get_bnDIP34() const
{
    return bn_dip34;
}

QPushButton *FireTabWgt::get_bnS2000_IP02() const
{
    return bn_S2000_IP02;
}

QPushButton *FireTabWgt::get_bnIPR513_3A() const
{
    return bn_IPR513_3A;
}

QPushButton *FireTabWgt::get_bnS_2000_IK() const
{
    return bn_S_2000_IK;
}

QPushButton *FireTabWgt::get_bnS_2000_PIK() const
{
    return bn_S_2000_PIK;
}

QPushButton *FireTabWgt::get_bnS_2000_SHIK() const
{
    return bn_S_2000_SHIK;
}

QPushButton *FireTabWgt::get_bnS_2000_V() const
{
    return bn_S_2000_V;
}

QPushButton *FireTabWgt::get_bnS_2000_ST() const
{
    return bn_S_2000_ST;
}

QPushButton *FireTabWgt::get_bnS_2000_SMK() const
{
    return bn_S_2000_SMK;
}

QPushButton *FireTabWgt::get_bnS_2000_KT() const
{
    return bn_S_2000_KT;
}

void FireTabWgt::setCheckedAllBns(bool checked)
{
    foreach (QPushButton* bn, v_bn) {
        bn->setChecked(checked);
    }
}

void FireTabWgt::setEnabledAllBns(bool enabled)
{
    foreach (QPushButton* bn, v_bn) {
        bn->setEnabled(enabled);
    }
}

void FireTabWgt::disableExcept(QString str)
{
    if(str == "DIP34")
    {
        bn_s2000->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(true);
        bn_s2000m->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if (str == "S2000")
    {
        bn_s2000->setChecked(true);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000m->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if (str == "KDL")
    {
        bn_s2000->setChecked(false);
        bn_kdl->setChecked(true);
        bn_dip34->setChecked(false);
        bn_s2000m->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if (str == "S2000M"){
        bn_s2000m->setChecked(true);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if (str == "S2000KS"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(true);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if (str == "S2000BI"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(true);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000BKI"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(true);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S20004"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(true);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000K"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(true);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000SP1"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(true);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000IP02"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(true);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "IPR513_3A"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(true);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000IK"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(true);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000PIK"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(true);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000SHIK"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(true);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000V"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(true);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000ST"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(true);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000SMK"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(true);
        bn_S_2000_KT->setChecked(false);
    }
    if(str == "S2000KT"){
        bn_s2000m->setChecked(false);
        bn_kdl->setChecked(false);
        bn_dip34->setChecked(false);
        bn_s2000->setChecked(false);
        bn_2000KS->setChecked(false);
        bn_s2000BI->setChecked(false);
        bn_s2000BKI->setChecked(false);
        bn_s2000K->setChecked(false);
        bn_s2000SP1->setChecked(false);
        bn_s2000_4->setChecked(false);
        bn_S2000_IP02->setChecked(false);
        bn_IPR513_3A->setChecked(false);
        bn_S_2000_IK->setChecked(false);
        bn_S_2000_PIK->setChecked(false);
        bn_S_2000_SHIK->setChecked(false);
        bn_S_2000_V->setChecked(false);
        bn_S_2000_ST->setChecked(false);
        bn_S_2000_SMK->setChecked(false);
        bn_S_2000_KT->setChecked(true);
    }

}
