#include "gui.h"
#include <QPixmap>
#include <QCursor>
#include <QWidget>
#include <QMainWindow>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QStringList>
#include <QMenuBar>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QRegExp>
#include <iostream>
#include "clickablelabel.h"
#include "utils.h"
#include "devicemanager.h"
#include "setupwidget.h"
#include "filesaver.h"
#include "smartdevice.h"
#include "plotter.h"
#include "sensor.h"
#include <QDebug>

struct GUI::GUIPrivate{
    QPixmap original_pixmap;
    QPixmap work_pxm;
    QCursor curTarget;
    QFileDialog *dialog = nullptr;
    QVBoxLayout * mainlayout = nullptr;
    QVBoxLayout * left_lay = nullptr;
    QHBoxLayout * toplayout = nullptr;
    //QHBoxLayout * figurelayout = nullptr;
    //QHBoxLayout * modelayout = nullptr;
    QHBoxLayout * bns_layout = nullptr;
    QHBoxLayout * bnMode_layout = nullptr;
    QVBoxLayout * bn_lines_lay = nullptr;
    QVBoxLayout * left_top_layout = nullptr;
    QMenu * pmnuFile = nullptr;
    QAction *msgAction = nullptr;
    QAction *msgSaveFile = nullptr;
    QAction *loadFile = nullptr;
    QGroupBox * left_grb = nullptr;
    ClickableLabel* screen_lbl = nullptr;
    MultiTabWgt * tabwgt = nullptr;
    QGroupBox * down_grb = nullptr;
    QLabel * ext_img_lbl = nullptr;
    QWidget* widget = nullptr;
    QGroupBox * bnsFig_grb = nullptr;
    QGroupBox * bnsMode_grb = nullptr;
    QGroupBox * bnsLine_grb = nullptr;
    QPushButton * bn_mode = nullptr;
    QPushButton * bn_fatline = nullptr;
    QPushButton * bn_slimline = nullptr;
    SetupWidget * setupwgt = nullptr;
};
//конструктор
GUI::GUI(QWidget *parent): QMainWindow(parent),data(std::make_unique<GUIPrivate>())
{
    createGUI();
    setSubSystem(SubSystem::NO_SUBSYSTEM);  ///надо сделать предупреждение, чтобы сперва выбиралась подсистема
}
//деструктор
GUI::~GUI()
{

}
//методы

//вывод на экран окошка пользовательского интерфейса
void GUI::createGUI()
{

    data->widget = new QWidget();
    data->mainlayout = new QVBoxLayout();
    data->left_lay = new QVBoxLayout();
    data->toplayout = new QHBoxLayout();
//    data->figurelayout = new QHBoxLayout();
//    data->modelayout = new QHBoxLayout();
    data->toplayout->addWidget(createTopLeftGroup());
//    data->figurelayout->addWidget(createFigBnsGroupBox());
//    data->modelayout->addWidget(createModeGroupBox());

    data->left_lay->addWidget(createFigBnsGroupBox());
    data->left_lay->addWidget(createLinesGroupBox());
    data->left_lay->addWidget(createModeGroupBox());
    data->toplayout->addLayout(data->left_lay);
    data->mainlayout->addLayout(data->toplayout);

//    data->mainlayout->addLayout(data->figurelayout);
//    data->mainlayout->addLayout(data->modelayout);
    data->mainlayout->addStretch(1);


    data->widget->setLayout(data->mainlayout);
    setCentralWidget(data->widget);
    data->pmnuFile = new QMenu(tr("&Файл"));
    data->msgAction = new QAction("Создать",data->pmnuFile);
    data->msgSaveFile = new QAction("Сохранить в файл", data->pmnuFile);
    data->loadFile = new QAction("Загрузить из файла", data->loadFile);
    data->pmnuFile->addAction(data->msgAction);
    data->pmnuFile->addAction(data->msgSaveFile);
    data->pmnuFile->addAction(data->loadFile);
    menuBar()->addMenu(data->pmnuFile);


    data->setupwgt = new SetupWidget(this);


    QObject::connect(data->msgAction, &QAction::triggered, this, &GUI::onFileOpen);
    QObject::connect(data->msgSaveFile, &QAction::triggered, this, &GUI::onSaveToFile);
    QObject::connect(data->loadFile, &QAction::triggered, this, &GUI::onLoadFile);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000(), &QPushButton::clicked, this, &GUI::onAddS2000Fire);
    QObject::connect(data->tabwgt->getFireTab()->get_bnDIP34(), &QPushButton::clicked, this, &GUI::onAddDip34);
    QObject::connect(data->tabwgt->getFireTab()->get_bnKDL(), &QPushButton::clicked, this, &GUI::onAddKDL);

//    QObject::connect(data->tabwgt->getLinesTab()->getBigLineBn() , &QPushButton::clicked, this, &GUI::onAddFatConnectionLine);
//    QObject::connect(data->tabwgt->getLinesTab()->getSmallLineBn() , &QPushButton::clicked, this, &GUI::onAddSlimConnectionLine);
    QObject::connect(data->bn_slimline, &QPushButton::clicked, this, &GUI::onSlimLine);
    QObject::connect(data->bn_fatline, &QPushButton::clicked, this, &GUI::onFatLine);

    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000(), &QPushButton::clicked, this, &GUI::onAddS2000Scud);
    QObject::connect(data->tabwgt->getSkudTab()->get_Foton(), &QPushButton::clicked, this, &GUI::onAddFoton);

    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000M(), &QPushButton::clicked, this, &GUI::onAddS2000_M_Scud);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000m(), &QPushButton::clicked, this, &GUI::onAddS2000_M_Fire);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000ks(), &QPushButton::clicked, this, &GUI::onAddS2000_KS_Fire);
    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000KS(), &QPushButton::clicked, this, &GUI::onAddS2000_KS_Scud);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000bi(), &QPushButton::clicked, this, &GUI::onAddS2000_BI_Fire);
    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000BI(), &QPushButton::clicked, this, &GUI::onAddS2000_BI_Scud);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000BKI(), &QPushButton::clicked, this, &GUI::onAddS2000_BKI_Fire);
    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000BKI(), &QPushButton::clicked, this, &GUI::onAddS2000_BKI_Scud);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000K(), &QPushButton::clicked, this, &GUI::onAddS2000_K_Fire);
    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000K(), &QPushButton::clicked, this, &GUI::onAddS2000_K_Scud);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000SP1(), &QPushButton::clicked, this, &GUI::onAddS2000_SP1_Fire);
    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000SP1(), &QPushButton::clicked, this, &GUI::onAddS2000_SP1_Scud);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000_4(), &QPushButton::clicked, this, &GUI::onAddS2000_4_Fire);
    QObject::connect(data->tabwgt->getSkudTab()->get_bnS2000_4(), &QPushButton::clicked, this, &GUI::onAddS2000_4_Scud);

    QObject::connect(data->tabwgt->getFireTab()->get_bnS2000_IP02(), &QPushButton::clicked, this, &GUI::onAdd_S2000IP02);
    QObject::connect(data->tabwgt->getFireTab()->get_bnIPR513_3A(), &QPushButton::clicked, this, &GUI::onAdd_IPR513_3A);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS_2000_IK(), &QPushButton::clicked, this, &GUI::onAdd_S2000IK);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS_2000_PIK(), &QPushButton::clicked, this, &GUI::onAdd_S2000PIK);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS_2000_SHIK(), &QPushButton::clicked, this, &GUI::onAdd_S2000SHIK);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS_2000_V(), &QPushButton::clicked, this, &GUI::onAdd_S2000V);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS_2000_ST(), &QPushButton::clicked, this, &GUI::onAdd_S2000ST);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS_2000_SMK(), &QPushButton::clicked, this, &GUI::onAdd_S2000SMK);
    QObject::connect(data->tabwgt->getFireTab()->get_bnS_2000_KT(), &QPushButton::clicked, this, &GUI::onAdd_S2000KT);

    QObject::connect(data->tabwgt->getSkudTab()->get_bn_FotonShEx(), &QPushButton::clicked, this, &GUI::onAdd_FotonShEx);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_StekloEx(), &QPushButton::clicked, this, &GUI::onAdd_StekloEx);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_ShoroxEx(), &QPushButton::clicked, this, &GUI::onAdd_ShoroxEx);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_MkEx(), &QPushButton::clicked, this, &GUI::onAdd_MkEx);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_STZex(), &QPushButton::clicked, this, &GUI::onAdd_STZex);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_IPDex(), &QPushButton::clicked, this, &GUI::onAdd_IPDex);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_IPDLex(), &QPushButton::clicked, this, &GUI::onAdd_IPDLex);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_IPPex(), &QPushButton::clicked, this, &GUI::onAdd_IPPex);
    QObject::connect(data->tabwgt->getSkudTab()->get_bn_IPRex(), &QPushButton::clicked, this, &GUI::onAdd_IPRex);

    QObject::connect(data->tabwgt->getTab(), &QTabWidget::currentChanged, this, &GUI::onTabChoosed);

    QObject::connect(data->bn_mode, &QPushButton::clicked, this, &GUI::onMode);
    QObject::connect(this, &GUI::s_TypeObj, data->screen_lbl, &ClickableLabel::onTypeObjectChanged);
    QObject::connect(data->pmnuFile, &QMenu::triggered, data->screen_lbl, &ClickableLabel::onMenuCalled);
}

QGroupBox *GUI::createTopLeftGroup()
{
    data->screen_lbl = new ClickableLabel(this,"Screen",this);

    data->screen_lbl->setAlignment(Qt::AlignTop | Qt::AlignLeft);


    QPixmap pix;
    pix.load("D:/QTProjects/CV_gui/matrix_test.bmp");
    SetOriginalPixmap(pix);

    data->screen_lbl->resize(data->original_pixmap.size());
    data->screen_lbl->setPixmap(data->original_pixmap);
    data->screen_lbl->show();

    data->left_grb = new QGroupBox(/*tr("left group")*/);
    data->left_top_layout = new QVBoxLayout();
    //data->left_top_layout->addStretch(1);
    data->left_top_layout->addWidget(data->screen_lbl);
    data->left_grb->setLayout(data->left_top_layout);

    return data->left_grb;
}


QGroupBox *GUI::createFigBnsGroupBox()
{
    data->tabwgt = new MultiTabWgt();
    data->bnsFig_grb = new QGroupBox();
    data->bns_layout = new QHBoxLayout();
    data->bns_layout->addWidget(data->tabwgt);
    data->bnsFig_grb->setLayout(data->bns_layout);
    return data->bnsFig_grb;
}

QGroupBox *GUI::createModeGroupBox()
{
    data->bnsMode_grb = new QGroupBox(tr("режим редактора"));
    data->bnMode_layout = new QHBoxLayout();
    data->bn_mode = new QPushButton("корректировать");
    data->bn_mode->setCheckable(true);
    data->bnMode_layout->addWidget(data->bn_mode);
    data->bnsMode_grb->setLayout(data->bnMode_layout);
    return data->bnsMode_grb;
}

QGroupBox *GUI::createLinesGroupBox()
{
    data->bnsLine_grb = new QGroupBox(tr("тип линий"));
    data->bn_lines_lay = new QVBoxLayout();
    data->bn_fatline = new QPushButton("линия RS485");
    data->bn_fatline->setCheckable(true);
    data->bn_slimline = new QPushButton("2 проводная линия");
    data->bn_slimline->setCheckable(true);
    data->bn_lines_lay->addWidget(data->bn_fatline);
    data->bn_lines_lay->addWidget(data->bn_slimline);
    data->bnsLine_grb->setLayout(data->bn_lines_lay);
    return data->bnsLine_grb;
}

void GUI::showMousePosition(QPoint pt)
{
    setWindowTitle(
                  QString::number(pt.x())+
                  QString(",")+
                  QString::number(pt.y())
                );
}

TypeObject GUI::getTypeObject() const
{
    return dobj;
}

void GUI::setMode(Mode m)
{
    mode = m;
}

Mode GUI::getMode()
{
    return mode;
}

LineRole GUI::getRole()
{
    return role;
}

void GUI::setRole(LineRole r)
{
    role = r;
}

SubSystem GUI::getSubSystem()
{
    return sub;
}

void GUI::setSubSystem(SubSystem ss)
{
    sub = ss;
}

void GUI::setType(TypeObject type)
{
    dobj = type;
}

TypeObject GUI::getType()
{
    return dobj;
}

void GUI::memTypeObject(TypeObject type)
{
    prev_typeobj = type;
}

TypeObject GUI::rememTypeObject()
{
    dobj = prev_typeobj;
    return prev_typeobj;
}

SetupWidget *GUI::getSetupWgt() const
{
    return data->setupwgt;
}

QString GUI::getPathToScheme()
{
    return fpath;
}

MultiTabWgt *GUI::getMultiTabWgt() const
{
    return data->tabwgt;
}



//-----------открытие файла c картинкой плана помещения-----------
void GUI::createSchemeActions()
{
    QString ftype;

    //для выполнения действий по пересчету масштаба рамки в случае ресайза картинки
    SetScaled(false);                   //в случае каждого нового переоткрытия файла отменить масштабирование


    //узнаем путь к файлу
    fpath = QFileDialog::getOpenFileName(this, tr("Открыть изображение"),
                       "D:/QTProjects/CV_gui", tr("Файлы рисунков и видео (*.jpg    *.png   *.avi)")); //путь к файлу

    if (fpath.isNull())
        return;

    QFileInfo info(fpath);

    //узнаем имя файла
    m_fileName = info.fileName();

    QFile file(fpath);               // создаем файл с именем файла
    if (!fpath.isEmpty())
    {
        if(!file.open(QIODevice::ReadOnly))   // и пытаемся его открыть только для чтения
        {
            QMessageBox::critical(nullptr, QObject::tr("Ошибка"), QObject::tr("Файл не может быть открыт"));
        }
    }
    //определяем расширение файла
    ftype = AnalyseFileType(fpath);
    //Если картинка
    if ((ftype == "jpg")||(ftype == "png")||(ftype == "bmp"))
    {
        data->work_pxm.load(fpath);
        ShowPicture(); //вывод картинки
    }
}

void GUI::openSchemeActions()
{
    static int dev_cnt = 0;
    static int line_cnt = 0;

    ///списки для устройств
    QList<int> d_listX;
    QList<int> d_listY;
    QList<int> d_listID;
    QList<int> d_listOwn;
    QStringList d_listRemID;
    QStringList d_listType;
    QList<int> d_listUsID;
    QStringList d_listSubSys;
    QStringList d_masterLine;
    QStringList d_model;

    ///списки для линий
    QList<int> l_listID;
    QStringList l_listRemID;
    QList<int> l_listUsID;
    QStringList l_listPts;
    QStringList l_listNotify;
    QStringList l_listRole;
    QStringList l_listSubSys;
    QStringList l_masterLine;

    fpath = QFileDialog::getOpenFileName(this, tr("Открыть существующий проект"),
                                         "D:/QTProjects/RedactorR3", tr("Файлы JSON (*.json)"));
    if (fpath.isNull())
        return;
    QFileInfo info(fpath);
    m_fileName = info.fileName();

    QFile file(fpath);

    if (!fpath.isEmpty())
    {
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(nullptr, QObject::tr("Ошибка"), QObject::tr("Файл не может быть открыт"));
        }
        else{
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            auto fileData = QString(stream.readAll()).toUtf8();
            QJsonParseError error;
            QJsonDocument jsondoc = QJsonDocument::fromJson(fileData, &error);
            if(!jsondoc.isObject())
                std::cout << "Parsing JSON object failed: " << error.errorString().toStdString() << std::endl;
            else{
                std::cout << "Creating root JSON object..." << std::endl;

                ///вытаскиваю имя и путь файла с картинкой

                QJsonObject jsonObj = jsondoc.object();
                QString path = jsonObj["scheme_path"].toString();
                fpath = path;

                ///вытаскиваю объекты
                /// 1. Все, что известно об устройствах
                QJsonArray jsonArray = jsonObj["dev_description"].toArray();
                foreach (const QJsonValue value, jsonArray) {

                    if(value.isObject()){
                        /// 1.1 координата X для отрисовки на схеме
                        int coordX = value["dev_coordinateX"].toString().toInt();
                        d_listX.push_back(coordX);


                        /// 1.2 координата Y для отрисовки на схеме
                        int coordY = value["dev_coordinateY"].toString().toInt();
                        d_listY.push_back(coordY);

                        /// 1.3 системный ID устройства
                        int valID = value["dev_id"].toString().toInt();
                        d_listID.push_back(valID);

                        /// 1.4 номер линии, к которой подключено устройство
                        int lineOwnerId = value["dev_line_owner"].toString().toInt();
                        d_listOwn.push_back(lineOwnerId);

                        /// 1.5 устройство исключено из схемы
                        QString removed = value["dev_removed"].toString();
                        d_listRemID.push_back(removed);

                        /// 1.6 тип устройства
                        QString type = value["dev_type"].toString();
                        d_listType.push_back(type);

                        /// 1.7 модель устройства
                        QString model = value["dev_model"].toString();
                        d_model.push_back(model);

                        /// 1.8 номер, который задал пользователь
                        int userId = value["dev_user_id"].toString().toInt();
                        d_listUsID.push_back(userId);

                        ///1.9 определяется подсистема
                        QString strSub = value["subsystem"].toString();
                        d_listSubSys.push_back(strSub);

                        ///1.10 мастер-линия
                        QString  strMast = value["masterLine"].toString();
                        d_masterLine.push_back(strMast);

                        dev_cnt++;
                    }
                }
                qDebug() << "------------------------";

                ///2. Все, что известно о линиях
                jsonArray = jsonObj["line_description"].toArray();
                foreach (const QJsonValue value, jsonArray) {
                    if(value.isObject()){

                        ///2.1 системный ID линии
                        int line_id = value["line_id"].toString().toInt();
                        l_listID.push_back(line_id);

                        ///2.2 линия исключена из схемы
                        QString removed = value["line_removed"].toString();
                        l_listRemID.push_back(removed);

                        ///2.3 номер, который присвоил пользователь
                        int userId = value["line_user_id"].toString().toInt();
                        l_listUsID.push_back(userId);

                        ///2.4 Список точек для построения на схеме
                        QString linePoints = value["line_points"].toString();
                        l_listPts.push_back(linePoints);

                        ///2.5 Список устройств линии
                        QString notifyer = value["notifiers"].toString();
                        l_listNotify.push_back(notifyer);

                        ///2.6 Линия обслуживает контроллеры или датчики
                        QString strRole = value["linerole"].toString();
                        l_listRole.push_back(strRole);

                        ///2.7 Определяется подсистема
                        QString strSub = value["subsystem"].toString();
                        l_listSubSys.push_back(strSub);

                        ///2.8 Мастер - линия
                        QString  strMast = value["masterLine"].toString();
                        l_masterLine.push_back(strMast);

                        line_cnt++;
                    }

                }
            }
        }
    }
    ///анализ JSON файла закончен
    ///
    /// Вывод картинки

    data->work_pxm.load(fpath);
    ShowPicture();

    auto &manager = DeviceManager::instance();

    ///построение объектов
    for(int i = 0; i < dev_cnt; i++){
        Devices * dev = nullptr;
        QPoint pt;

        if (d_listType[i] == "controller"){
            pt.setX(d_listX[i] + GUI_Constants::CTRL_WIDTH / 2);
            pt.setY(d_listY[i] + GUI_Constants::CTRL_HEIGHT / 2);
            dev = dynamic_cast<SmartDevice*>(manager.makeItem(d_model[i], d_listSubSys[i], pt));
            dev->setType(TypeObject::PLUGGABLE_TO485/*typeid(*dev).name()*/);
            //qDebug() << "controller/ typeid = " << typeid(*dev).name();

        }

        else if (d_listType[i] == "sensor"){
            bool ok;
            pt.setX(d_listX[i] + GUI_Constants::SENS_RADIUS / 2);
            pt.setY(d_listY[i] + GUI_Constants::SENS_RADIUS / 2);
            dev = dynamic_cast<Sensor*>(manager.makeItem(d_model[i], d_listSubSys[i], pt));
            dev->setType(TypeObject::PLUGGABLE_TO2WIRE/*typeid(*dev).name()*/);
            //qDebug() << "sensor/ typeid = " << typeid(*dev).name();
            QString str = d_masterLine[i];
            int val =  str.toInt(&ok,10);
            dev->setMasterLineNum(val);
        }

        dev->setId(d_listID[i]);
        dev->setUserId(d_listUsID[i]);
        dev->setNotifierId(d_listOwn[i]);


        if(d_listRemID[i] == "true"){
            dev->setRemoved(true);
        }
        else if(d_listRemID[i] == "false"){
            dev->setRemoved(false);
        }

        ///--------
        if(d_listSubSys[i] == "fire"){
            dev->setSubSystem(SubSystem::FIRE);
        }
        else if(d_listSubSys[i] == "skud"){
            dev->setSubSystem(SubSystem::SKUD);
        }
        /// --------

        manager.addDevice(dev);

    }

    ///построение линий


    QString sX;
    QString sY;

    QRegExp rx("(\\ |\\,|\\.|\\;|\\:|\\t|\\""|\\n)");   ///это регулярное выражение
                                                        ///применимо и на лист точек, и лист с номерами устройств

    for(int i = 0; i < line_cnt; i++){
        ConnectionLine * line = new ConnectionLine();
        line->setId(l_listID[i]);
        line->setUserId(l_listUsID[i]);
        if(l_listRemID[i] == "true"){
            line->setRemoved(true);
        }
        else if(l_listRemID[i] == "false"){
            line->setRemoved(false);
        }

        if(l_listRole[i] == "rs485line"){
            line->setRole(LineRole::RS485LINE);
        }
        else if(l_listRole[i] == "dualwire"){
            line->setRole(LineRole::DUALWIRELINE);
            bool ok;
            QString str = l_masterLine[i];
            int val =  str.toInt(&ok,10);
            line->setMasterLineNum(val);
        }

        if(l_listSubSys[i] == "fire"){
            line->setSubSystem(SubSystem::FIRE);
        }
        else if(l_listSubSys[i] == "skud"){
            line->setSubSystem(SubSystem::SKUD);
        }


        QString str_pt(l_listPts[i]);

        QStringList strlst_pt = str_pt.split(rx);

        for(int i = 0; i < strlst_pt.length(); i++){
            QPoint pt;
            if(i % 2 == 0){
                sX = strlst_pt[i];

            }
            else{
                sY = strlst_pt[i];
                pt.setX(sX.toInt());
                pt.setY(sY.toInt());
                line->addKeyPoint(pt);
            }
        }

        QString str_noty(l_listNotify[i]);
        QStringList strlst_noty = str_noty.split(rx);
        foreach (QString var, strlst_noty) {
            line->addSubscriber(QString(var).toInt());
        }

        manager.addConnectionLine(line);
    }
    dev_cnt = 0;
    line_cnt = 0;
    setJSONloaded(true);

}

//-------------------------------------------------------------------

//void GUI::setCursorSize(cursor_size s)
//{
//    switch (s) {
//    case 0:
//        current_size = small_cur;
//        break;
//    case 1:
//        current_size = big_cur;
//        break;
//    default:
//        current_size = small_cur;;
//        break;
//    };
//}

void GUI::SetScaled(bool scaled)
{
    this->pict_scaled = scaled;
}


bool GUI::GetScaled()
{
    return this->pict_scaled;
}



QPixmap &GUI::GetOriginalPixmap()
{
    return data->original_pixmap;
}

void GUI::SetOriginalPixmap(QPixmap pix)
{
    data->original_pixmap = pix;
}

void GUI::SetCalculateResizeCoefft(int before_resize, int after_resize)
{
    this->scale_coef = (double)after_resize / before_resize;
}


double GUI::GetCalculateResizeCoefft()
{
    return this->scale_coef;
}

QString GUI::AnalyseFileType(QString fpath)
{
    //определяем расширение файла (картинка/видео?)
    QString str;
    int i = fpath.indexOf(".");
    if (i>0)
    {
        str = fpath;
        str.remove(0,i+1);
    }
    return str;
}

QPixmap GUI::AnalysePictureResolution()
{
    //выводим загруженную картинку на форму

    //анализируем картинку. Рассматриваем 4 случая:
                                        //ширина и высота > 800x600
                                        //ширина >800, высота нормальная (<=600)
                                        //высота >600, ширина нормальная (<=800)
                                        //ширина и высота < 800x600
    //1- й случай
    if((GUI_Constants::MAX_WIDTH < data->work_pxm.width())&&(GUI_Constants::MAX_HEIGHT < data->work_pxm.height()))
    {
        SetScaled(true);
        width_before = data->work_pxm.width();//запомнил изначальную ширину и высоту
        heigth_before = data->work_pxm.height();

        //Ресайзаем. Такой способ не искажает соотношение сторон после ресайза
        QSize picsize(GUI_Constants::MAX_WIDTH,GUI_Constants::MAX_HEIGHT);
        SetOriginalPixmap(data->work_pxm); //сохранили оригинал картинки
        data->work_pxm = data->work_pxm.scaled(picsize,Qt::KeepAspectRatio);
        //считаем коэффициент перемасштабирования рамки захвата
        SetCalculateResizeCoefft(width_before, data->work_pxm.width());
    }
    //2- й случай
    else if (GUI_Constants::MAX_WIDTH < data->work_pxm.width())
    {
        SetScaled(true);
        width_before = data->work_pxm.width();

        QSize picsize(GUI_Constants::MAX_WIDTH, data->work_pxm.height());
        SetOriginalPixmap(data->work_pxm); //сохранили оригинал картинки
        data->work_pxm = data->work_pxm.scaled(picsize,Qt::KeepAspectRatio);
        SetCalculateResizeCoefft(width_before,data->work_pxm.width());
    }

    //3 - й случай
    else if (GUI_Constants::MAX_HEIGHT < data->work_pxm.height())
    {

        SetScaled(true);
        heigth_before = data->work_pxm.height();

        QSize picsize(data->work_pxm.width(),GUI_Constants::MAX_HEIGHT);
        SetOriginalPixmap(data->work_pxm); //сохранили оригинал картинки
        data->work_pxm = data->work_pxm.scaled(picsize,Qt::KeepAspectRatio);
        SetCalculateResizeCoefft(heigth_before,data->work_pxm.height());
    }
    //4-й случай
    else
    {
        SetScaled(false);
        SetOriginalPixmap(data->work_pxm);
    }
    return data->work_pxm;
}

void GUI::ShowPicture()
{
    QPixmap pix = AnalysePictureResolution();
    data->screen_lbl->resize(pix.size());
    data->screen_lbl->setPixmap(pix);
    data->screen_lbl->show();
}

void GUI::setJSONloaded(bool flag)
{
    this->json_loaded = flag;
}

bool GUI::isJSONloaded()
{
    return this->json_loaded;
}

void GUI::onFileOpen()
{
    createSchemeActions();
}

void GUI::onSaveToFile()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Json File"),
                                                        QString(),
                                                        tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);
    QDir::setCurrent(fileInfo.path());

    FileSaver::instance().setBackgroundScheme(this->getPathToScheme());
    FileSaver::instance().makeJsonObject();
    FileSaver::instance().saveToFile(saveFileName);


}

void GUI::onLoadFile()
{
    openSchemeActions();
}

void GUI::onTabChoosed()
{
    dobj = TypeObject::NO_DEV;
    if(data->tabwgt->getTab()->currentIndex() == 0){
    }

    if(data->tabwgt->getTab()->currentIndex() == 1){
        setSubSystem(SubSystem::FIRE);
    }

    if(data->tabwgt->getTab()->currentIndex() == 2){
        setSubSystem(SubSystem::SKUD);
    }
}

void GUI::onAddS2000Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000);
    manager.setS2000SubSystem(SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000);
    manager.setS2000SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S2000");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_M_Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_M);
    manager.setS2000_M_SubSystem(SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000M");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_M_Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_M);
    manager.setS2000_M_SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S2000M");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_KS_Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_KS);
    manager.setS2000_KS_SubSystem( SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000KS");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_KS_Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_KS);
    manager.setS2000_KS_SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S2000KS");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_BI_Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_BI);
    manager.setS2000_BI_SubSystem( SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000BI");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_BI_Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_BI);
    manager.setS2000_BI_SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S2000BI");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_BKI_Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_BKI);
    manager.setS2000_BKI_SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S2000BKI");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_BKI_Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_BKI);
    manager.setS2000_BKI_SubSystem(SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000BKI");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_K_Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_K);
    manager.setS2000_K_SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S2000K");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_K_Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_K);
    manager.setS2000_K_SubSystem(SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000K");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_4_Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_4);
    manager.setS2000_4_SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S20004");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_4_Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_4);
    manager.setS2000_4_SubSystem(SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S20004");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_SP1_Scud(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_SP1);
    manager.setS2000_SP1_SubSystem(SubSystem::SKUD);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("S2000SP1");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddS2000_SP1_Fire(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_SP1);
    manager.setS2000_SP1_SubSystem(SubSystem::FIRE);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000SP1");
    setSubSystem(SubSystem::FIRE);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddFoton(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::FOTON4);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("foton");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_FotonShEx(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::FotonShEx);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("FotonShEx");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_StekloEx(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::StekloEx);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("StekloEx");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_ShoroxEx(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::ShoroxEx);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("ShoroxEx");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_MkEx(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::MkEx);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("MkEx");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_STZex(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::STZex);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("STZex");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_IPDex(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::IPDex);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("IPDex");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_IPDLex(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::IPDLex);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("IPDLex");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_IPPex(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::IPPex);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("IPPex");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_IPRex(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::IPRex);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->disableExcept("IPRex");
    setSubSystem(SubSystem::SKUD);
    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddDip34(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::DIP34);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("DIP34");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000IP02(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S2000_IP02);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000IP02");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_IPR513_3A(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::IPR513_3A);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("IPR513_3A");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000IK(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_IK);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000IK");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000PIK(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_PIK);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000PIK");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000SHIK(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_SHIK);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000SHIK");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000V(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_V);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000V");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000ST(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_ST);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000ST");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000SMK(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_SMK);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000SMK");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAdd_S2000KT(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::S_2000_KT);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("S2000KT");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO2WIRE;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddKDL(bool lock)
{
    auto &manager = DeviceManager::instance();
    manager.setCurModel(Models::KDL);
    //data->tabwgt->getLinesTab()->setCheckedAllBns(false);
    data->tabwgt->getSkudTab()->setCheckedAllBns(false);
    data->tabwgt->getFireTab()->disableExcept("KDL");
    setSubSystem(SubSystem::FIRE);

    if(lock){
        dobj = TypeObject::PLUGGABLE_TO485;
        memTypeObject(dobj);
    }
    else{
        dobj = TypeObject::NO_DEV;
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddFatConnectionLine(bool lock)
{
    if(lock){
        data->screen_lbl->lockLine();
        data->screen_lbl->setLineInProcess();
        data->screen_lbl->setClickCnt(0);
        //data->tabwgt->getLinesTab()->getSmallLineBn()->setChecked(false);
        data->tabwgt->getFireTab()->setCheckedAllBns(false);
        data->tabwgt->getSkudTab()->setCheckedAllBns(false);
        role = LineRole::RS485LINE;
        dobj = TypeObject::LINE;
    }
    else{
        data->screen_lbl->unlockLine();
        data->screen_lbl->finishLine();
        rememTypeObject();
    }
    emit s_TypeObj(dobj);
}

void GUI::onAddSlimConnectionLine(bool lock)
{
    if(lock){
        data->screen_lbl->lockLine();
        data->screen_lbl->setLineInProcess();
        data->screen_lbl->setClickCnt(0);
        //data->tabwgt->getLinesTab()->getBigLineBn()->setChecked(false);
        data->tabwgt->getFireTab()->setCheckedAllBns(false);
        data->tabwgt->getSkudTab()->setCheckedAllBns(false);
        role = LineRole::DUALWIRELINE;
        dobj = TypeObject::LINE;
    }
    else{
        data->screen_lbl->unlockLine();
        data->screen_lbl->finishLine();
        rememTypeObject();
    }
    emit s_TypeObj(dobj);
}

void GUI::onMode(bool pressed)
{
    if(pressed){
        setMode(Mode::CORRECT);
        data->bn_mode->setText("рисовать");
        //data->tabwgt->getLinesTab()->setEnabledAllBns(false);
        data->tabwgt->getFireTab()->setEnabledAllBns(false);
        data->tabwgt->getSkudTab()->setEnabledAllBns(false);
        data->bn_slimline->setChecked(false);
        data->bn_fatline->setChecked(false);
        data->bn_fatline->setEnabled(false);
        data->bn_slimline->setEnabled(false);
    }
    else{
        setMode(Mode::DRAW);
        data->bn_mode->setText("корректировать");
        //data->tabwgt->getLinesTab()->setEnabledAllBns(true);
        data->tabwgt->getFireTab()->setEnabledAllBns(true);
        data->tabwgt->getSkudTab()->setEnabledAllBns(true);
        data->bn_slimline->setChecked(false);
        data->bn_fatline->setChecked(false);
        data->bn_slimline->setEnabled(true);
        data->bn_fatline->setEnabled(true);
    }
    dobj = TypeObject::NO_DEV;
}

void GUI::onFatLine(bool pressed)
{

    ///-----
    if(pressed){
        data->screen_lbl->lockLine();
        data->screen_lbl->setLineInProcess();
        data->screen_lbl->setClickCnt(0);
        data->bn_slimline->setChecked(false);
        //data->tabwgt->getLinesTab()->getSmallLineBn()->setChecked(false);
        data->tabwgt->getFireTab()->setCheckedAllBns(false);
        data->tabwgt->getSkudTab()->setCheckedAllBns(false);
        role = LineRole::RS485LINE;
        dobj = TypeObject::LINE;
    }
    else{
        data->screen_lbl->unlockLine();
        data->screen_lbl->finishLine();
        rememTypeObject();
    }
    emit s_TypeObj(dobj);
}

void GUI::onSlimLine(bool pressed)
{
    ///-----
    if(pressed){
        data->screen_lbl->lockLine();
        data->screen_lbl->setLineInProcess();
        data->screen_lbl->setClickCnt(0);
        data->bn_fatline->setChecked(false);
        //data->tabwgt->getLinesTab()->getBigLineBn()->setChecked(false);
        data->tabwgt->getFireTab()->setCheckedAllBns(false);
        data->tabwgt->getSkudTab()->setCheckedAllBns(false);
        role = LineRole::DUALWIRELINE;
        dobj = TypeObject::LINE;
    }
    else{
        data->screen_lbl->unlockLine();
        data->screen_lbl->finishLine();
        rememTypeObject();
    }
    emit s_TypeObj(dobj);
}








