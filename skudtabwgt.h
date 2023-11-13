#ifndef SKUDTABWGT_H
#define SKUDTABWGT_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QVector>

class SkudTabWgt : public QWidget
{
    Q_OBJECT
public:
    explicit SkudTabWgt(QWidget *parent = 0);
    ~SkudTabWgt();
private:
    QVector<QPushButton*> v_bn;
    QVBoxLayout * mainLayout = nullptr;
    QGroupBox * devGroup = nullptr;
    QGroupBox * sensGroup = nullptr;
    QGridLayout * devGridLay = nullptr;
    QGridLayout * sensGridLay = nullptr;
    QPushButton * bn_s2000 = nullptr;
    QPushButton * bn_s2000m = nullptr;
    QPushButton * bn_s2000KS = nullptr;
    QPushButton * bn_s2000BI = nullptr;
    QPushButton * bn_foton = nullptr;
    QPushButton * bn_s2000BKI = nullptr;
    QPushButton * bn_s2000K = nullptr;
    QPushButton * bn_s2000SP1 = nullptr;
    QPushButton * bn_s2000_4 = nullptr;
    QPushButton * bn_FotonShEx = nullptr;
    QPushButton * bn_StekloEx = nullptr;
    QPushButton * bn_ShoroxEx = nullptr;
    QPushButton * bn_MkEx = nullptr;
    QPushButton * bn_STZex = nullptr;
    QPushButton * bn_IPDex = nullptr;
    QPushButton * bn_IPDLex = nullptr;
    QPushButton * bn_IPPex = nullptr;
    QPushButton * bn_IPRex = nullptr;

    QGroupBox *createSensGroup();
    QGroupBox *createDevsGroup();

public:
    QPushButton *get_bnS2000() const;
    QPushButton *get_Foton() const;
    QPushButton *get_bnS2000M() const;
    QPushButton *get_bnS2000KS() const;
    QPushButton *get_bnS2000BI() const;
    QPushButton *get_bnS2000BKI() const;
    QPushButton *get_bnS2000K() const;
    QPushButton *get_bnS2000SP1() const;
    QPushButton *get_bnS2000_4() const;

    QPushButton * get_bn_FotonShEx() const;
    QPushButton * get_bn_StekloEx() const;
    QPushButton * get_bn_ShoroxEx() const;
    QPushButton * get_bn_MkEx() const;
    QPushButton * get_bn_STZex() const;
    QPushButton * get_bn_IPDex() const;
    QPushButton * get_bn_IPDLex() const;
    QPushButton * get_bn_IPPex() const;
    QPushButton * get_bn_IPRex() const;


    void setCheckedAllBns(bool checked);
    void setEnabledAllBns(bool enabled);
    void disableExcept(QString str);
};

#endif // SKUDTABWGT_H
