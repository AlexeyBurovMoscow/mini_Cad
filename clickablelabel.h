#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QLabel>
#include <QPainter>
#include <QMenu>
#include <QPoint>
#include "plotter.h"

class Plotter;
class GUI;

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(GUI *gui, QWidget* parent = nullptr);
    explicit ClickableLabel(GUI *gui, const QString& text, QWidget* parent = nullptr);
    ~ClickableLabel();

private:
    int line_cnt = 0;
    int dev_cnt = 0;
    bool line_finded = false;
    bool dev_finded = false;
    bool cme = false;   //context menu enabled
    bool le = false;   //line enable. Разрешаем строить линию в режиме редактирования
    bool line_process = false;  //продолжать ввод линии или нет
    bool blink = false;
    int counter = 0;
    int current_line = 0;
    int click_cnt = 0;

    GUI* gui_owner = nullptr;
    QMenu * menu_ctx = nullptr; //контекстное меню - правой кнопкой мыши по значку
    QMenu * menu_line = nullptr;    //контекстное меню линии - завершить ввод или нет
    ClickableLabel * screen = nullptr;
    QPixmap * qpm = nullptr;
    int cursor_x = 0;
    int cursor_y = 0;

    int selected_cur_x = 0;
    int selected_cur_y = 0;

    int left_top_corner_coordX = 0;
    int left_top_corner_coordY = 0;

    int left_down_corner_coordX = 0;
    int left_down_corner_coordY = 0;

    int right_top_corner_coordX = 0;
    int right_top_corner_coordY = 0;

    int right_down_corner_coordX = 0;
    int right_down_corner_coordY = 0;

    QPainter p;
    Plotter * plotter = nullptr;
    TypeObject m_type;
    Mode mode;

    QPoint point{0,0};


protected:
    virtual void mouseMoveEvent(QMouseEvent *ev);               //переопределяет событие движения курсора по области картинки
    virtual void mousePressEvent(QMouseEvent *ev);              //переопределяет нажатие кнопки мыши
    virtual void paintEvent(QPaintEvent *evt);                  //переопределяем событие рисования
    virtual void timerEvent(QTimerEvent *);                     //переоопределяем событие таймера (сам таймер - см в конструкторе)
    virtual void contextMenuEvent( QContextMenuEvent* event );  //для контекстного меню, на значке устройства - правой клавишей мыши

    void markPictureRegion(QPaintEvent *evt);
    void highLightDevice(QPaintEvent *evt);

public:
    void connectMenu();
    void enableMenu();
    void disableMenu();
    bool isMenuEnabled();


    void setClickCnt(int cnt);
    int getClickCnt();
    void incrementClickCnt();

    void lockLine();
    void unlockLine();
    bool isLineLocked();

    void finishLine();
    void setLineInProcess();
    bool isLineProcess();

    QPoint getMousePosition() const;

    TypeObject getTypeObject() const;
    void setMode(Mode m);
    Mode getMode();

    void setActualLineNumber(int num);
    int getActualLineNumber();

    TypeObject getType() const;
    void setType(TypeObject type);
    void setType(const char* type);

    void endLine();

    void setLineCount(int val);
    int getLineCnt();
    void incrLineCnt();
    void decrLineCnt();

    void setDevCnt();
    int getDevCnt();
    void incrDevCnt();



signals:
    void clicked();

public slots:
    void onTypeObjectChanged(TypeObject type);
    void onRemoveAction();
    void onEndLineAction();
    void onSetupAction();
    void onMenuCalled();

};

#endif // CLICKABLELABEL_H
