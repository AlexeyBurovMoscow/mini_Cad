#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QPoint>
#include <QGroupBox>
#include <QPushButton>
#include <QByteArray>
#include <memory>
#include "utils.h"
#include "multitabwgt.h"

class SetupWidget;
class GUI: public QMainWindow
{
    Q_OBJECT
    struct GUIPrivate;
    std::unique_ptr<GUIPrivate> data;
public:
    explicit GUI(QWidget *parent = 0);
    ~GUI();

    void createGUI();


private:

    TypeObject dobj;
    LineRole role;
    SubSystem sub;
    TypeObject prev_typeobj;

    Mode mode = Mode::DRAW;


    //механика работы с курсором

    //enum cursor_size{small_cur, big_cur} current_size;
    bool pict_scaled = false;
    bool pict_scaled_horizontal = false;
    bool pict_scaled_vertical = false;
    double scale_coef;


    //механика работы с файлом
    QString  m_fileName;
    QString fpath;
    bool json_loaded = false;

    //механика для работы с картинкой
    int width_before = 0;
    int heigth_before = 0;

    int area_around = 0;

    int left_top_corner_coordX;
    int left_top_corner_coordY;

    int left_down_corner_coordX;
    int left_down_corner_coordY;

    int right_top_corner_coordX;
    int right_top_corner_coordY;

    int right_down_corner_coordX;
    int right_down_corner_coordY;

    //методы, создающие группы виджетов:
    QGroupBox *createTopLeftGroup();
    QGroupBox *createFigBnsGroupBox();
    QGroupBox *createModeGroupBox();
    QGroupBox *createLinesGroupBox();

public:
    //методы пользовательского интерфейса
    void createSchemeActions(); ///открывается png или jpg с планом помещения
    void openSchemeActions();   ///открываем json файл, из которого выгружаем подготовленный проект

public:
    void SetScaled(bool scaled);        //установить флаг перемасштабирования картинки (и рамки курсора)
    bool GetScaled();
    QPixmap &GetOriginalPixmap();
    void SetOriginalPixmap(QPixmap work_pxm);
    void SetCalculateResizeCoefft(int before_resize, int after_resize);//расчитать и установить коэффициент перемасштабирования рамки
    double GetCalculateResizeCoefft();
    QString AnalyseFileType(QString fpath);
    QPixmap AnalysePictureResolution();

    void setJSONloaded(bool flag);
    bool isJSONloaded();
    void showMousePosition(QPoint pt);
    TypeObject getTypeObject() const;
    void memTypeObject(TypeObject type);
    TypeObject rememTypeObject();
    QString getPathToScheme();


    void setMode(Mode m);
    Mode getMode();
    void ShowPicture();
    LineRole getRole();
    void setRole(LineRole r);
    SubSystem getSubSystem();
    void setSubSystem(SubSystem ss);
    void setType(TypeObject type);
    TypeObject getType();

    SetupWidget * getSetupWgt() const;
    MultiTabWgt * getMultiTabWgt() const;

private slots:
    void onFileOpen();
    void onSaveToFile();
    void onLoadFile();
    void onTabChoosed();
    void onAddS2000Fire(bool lock);
    void onAddS2000Scud(bool lock);
    void onAddS2000_M_Fire(bool lock);
    void onAddS2000_M_Scud(bool lock);
    void onAddS2000_KS_Fire(bool lock);
    void onAddS2000_KS_Scud(bool lock);
    void onAddS2000_BI_Fire(bool lock);
    void onAddS2000_BI_Scud(bool lock);
    void onAddS2000_BKI_Scud(bool lock);
    void onAddS2000_BKI_Fire(bool lock);
    void onAddS2000_K_Scud(bool lock);
    void onAddS2000_K_Fire(bool lock);
    void onAddS2000_4_Scud(bool lock);
    void onAddS2000_4_Fire(bool lock);
    void onAddS2000_SP1_Scud(bool lock);
    void onAddS2000_SP1_Fire(bool lock);
    void onAddFoton(bool lock);
    ///-----
    void onAdd_FotonShEx(bool lock);
    void onAdd_StekloEx(bool lock);
    void onAdd_ShoroxEx(bool lock);
    void onAdd_MkEx(bool lock);
    void onAdd_STZex(bool lock);
    void onAdd_IPDex(bool lock);
    void onAdd_IPDLex(bool lock);
    void onAdd_IPPex(bool lock);
    void onAdd_IPRex(bool lock);
    ///------
    void onAddDip34(bool lock);
    void onAdd_S2000IP02(bool lock);
    void onAdd_IPR513_3A(bool lock);
    void onAdd_S2000IK(bool lock);
    void onAdd_S2000PIK(bool lock);
    void onAdd_S2000SHIK(bool lock);
    void onAdd_S2000V(bool lock);
    void onAdd_S2000ST(bool lock);
    void onAdd_S2000SMK(bool lock);
    void onAdd_S2000KT(bool lock);
    void onAddKDL(bool lock);
    void onAddFatConnectionLine(bool lock);
    void onAddSlimConnectionLine(bool lock);
    void onMode(bool pressed);
    void onFatLine(bool pressed);
    void onSlimLine(bool pressed);

signals:
    s_TypeObj(TypeObject type);
    void mousePress(QMouseEvent *event);


};

#endif // GUI_H
