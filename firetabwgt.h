#ifndef FIRETABWGT_H
#define FIRETABWGT_H

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QVector>

class FireTabWgt : public QWidget
{
    Q_OBJECT
public:
    explicit FireTabWgt(QWidget *parent = 0);
    ~FireTabWgt();

private:
    QVector<QPushButton*> v_bn;
    QVBoxLayout * mainLayout = nullptr;
    QGroupBox * devGroup = nullptr;
    QGroupBox * sensGroup = nullptr;
    QGridLayout * devGridLay = nullptr;
    QGridLayout * sensGridLay = nullptr;
    QPushButton * bn_s2000 = nullptr;
    QPushButton * bn_s2000m = nullptr;
    QPushButton * bn_2000KS = nullptr;
    QPushButton * bn_s2000BI = nullptr;
    QPushButton * bn_s2000BKI = nullptr;
    QPushButton * bn_s2000K = nullptr;
    QPushButton * bn_s2000SP1 = nullptr;
    QPushButton * bn_s2000_4 = nullptr;
    QPushButton * bn_kdl = nullptr;
    QPushButton * bn_dip34 = nullptr;
    QPushButton * bn_S2000_IP02 = nullptr;
    QPushButton * bn_IPR513_3A = nullptr;
    QPushButton * bn_S_2000_IK = nullptr;
    QPushButton * bn_S_2000_PIK = nullptr;
    QPushButton * bn_S_2000_SHIK = nullptr;
    QPushButton * bn_S_2000_V = nullptr;
    QPushButton * bn_S_2000_ST = nullptr;
    QPushButton * bn_S_2000_SMK = nullptr;
    QPushButton * bn_S_2000_KT = nullptr;


    QGroupBox *createSensGroup();
    QGroupBox *createDevsGroup();

public:
    QPushButton *get_bnS2000() const;
    QPushButton *get_bnS2000m() const;
    QPushButton *get_bnS2000ks() const;
    QPushButton *get_bnS2000bi() const;
    QPushButton *get_bnS2000BKI() const;
    QPushButton *get_bnS2000K() const;
    QPushButton *get_bnS2000SP1() const;
    QPushButton *get_bnS2000_4() const;
    QPushButton *get_bnKDL() const;
    QPushButton *get_bnDIP34() const;
    QPushButton *get_bnS2000_IP02() const;
    QPushButton *get_bnIPR513_3A() const;
    QPushButton *get_bnS_2000_IK() const;
    QPushButton *get_bnS_2000_PIK() const;
    QPushButton *get_bnS_2000_SHIK() const;
    QPushButton *get_bnS_2000_V() const;
    QPushButton *get_bnS_2000_ST() const;
    QPushButton *get_bnS_2000_SMK() const;
    QPushButton *get_bnS_2000_KT() const;

    void setCheckedAllBns(bool checked);
    void setEnabledAllBns(bool enabled);
    void disableExcept(QString str);


};

#endif // FIRETABWGT_H
