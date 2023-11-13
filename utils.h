#ifndef UTILS_H
#define UTILS_H

#include <QString>

namespace GUI_Constants {

    const int MAX_WIDTH = 1024;
    const int MAX_HEIGHT = 768;
    const int CTRL_WIDTH = 15;
    const int CTRL_HEIGHT = 30;
    const int SENS_RADIUS = 15;
}

enum Models{
    S_2000,
    S_2000_M,
    S_2000_KS,
    S_2000_BI,
    S_2000_BKI,
    S_2000_K,
    S_2000_4,
    S_2000_SP1,
    S2000_IP02,
    IPR513_3A,
    S_2000_IK,
    S_2000_PIK,
    S_2000_SHIK,
    S_2000_V,
    S_2000_ST,
    S_2000_SMK,
    S_2000_KT,
    FotonShEx,
    StekloEx,
    ShoroxEx,
    MkEx,
    STZex,
    IPDex,
    IPDLex,
    IPPex,
    IPRex,
    KDL,
    DIP34,
    FOTON4,
    NO_MODEL
};

enum TypeObject{
    PLUGGABLE_TO485,
    PLUGGABLE_TO2WIRE,
    LINE,
    NO_DEV,
    ANY_DEV
};

enum Mode{
    DRAW,
    CORRECT
};

enum LineRole{
    RS485LINE,
    DUALWIRELINE
};

enum SubSystem{
    FIRE,
    SKUD,
    NO_SUBSYSTEM
};





#endif // UTILS_H
