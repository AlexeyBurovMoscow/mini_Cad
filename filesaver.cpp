#include "filesaver.h"
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>
#include <QFileInfo>
#include <QListIterator>
#include <QVariant>
#include <QPoint>
#include "devices.h"
#include "connectionline.h"
#include "devicemanager.h"
#include "utils.h"
#include <QDebug>


struct FileSaver::FileSaverPrivate{
    bool opened = false;

    QString path_to_scheme;
    QFile * mFile = nullptr;
    ///текущий объект JSON с которым производится работа
    QJsonObject m_currentJsonObject;
};
FileSaver::FileSaver():
    fsaverPrivate(std::make_unique<FileSaverPrivate>()){}

FileSaver::~FileSaver(){}

FileSaver &FileSaver::instance()
{
    static FileSaver fsaver;
    return fsaver;
}

void FileSaver::saveToFile(QString fname)
{
    QFile jsonFile(fname);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }
    /// Записываем текущий объект Json в файл
    jsonFile.write(QJsonDocument(fsaverPrivate->m_currentJsonObject).toJson(QJsonDocument::Indented));
    jsonFile.close();   /// Закрываем файл
}

void FileSaver::setBackgroundScheme(QString fname)
{
    fsaverPrivate->path_to_scheme = fname;
}

void FileSaver::makeJsonObject()
{
    auto manager = DeviceManager::instance();
    QJsonArray textsArray;

    ///-------------путь к файлу с исходным планом---------------------------
    fsaverPrivate->m_currentJsonObject["scheme_path"] = fsaverPrivate->path_to_scheme;

///-------------вытаскиваем всю информацию об имеющихся устройствах------
    QListIterator<Devices*> it(manager.getDevices());
    if(!manager.getDevices().isEmpty()){
        while(it.hasNext()){
            Devices * dev = it.next();
            QJsonObject textObject;

 ///1.1. системный ID устройства
            textObject["dev_id"] = QString::number(dev->getId());

 ///1.2. Контроллер или датчик
            if(dev->getType() == TypeObject::PLUGGABLE_TO485){
                textObject["dev_type"] = "controller";
            }
            else if(dev->getType() == TypeObject::PLUGGABLE_TO2WIRE){
                textObject["dev_type"] = "sensor";
            }
///1.3  Модель устройства
            textObject["dev_model"] = dev->getModel();
///1.4. Удален пользователем
            textObject["dev_removed"] = QVariant(dev->isRemoved()).toString();
///1.5. Номер, который задал пользователь
            textObject["dev_user_id"] = QString::number(dev->getUserId());
///1.6. Номер шлейфа - "владельца" устройства
            textObject["dev_line_owner"] = QString::number(dev->getNotifierId());
///1.7. Стартовая координата отрисовки по X
            textObject["dev_coordinateX"] = QString::number(dev->getStartXpt());
///1.8. Стартовая координата отрисовки по Y
            textObject["dev_coordinateY"] = QString::number(dev->getStartYpt());
///1.9. Подсистема, к которой относится
            if(dev->getSubSystem() == SubSystem::FIRE){
                textObject["subsystem"] = "fire";
            }
            else if(dev->getSubSystem() == SubSystem::SKUD){
                textObject["subsystem"] = "skud";
            }
///1.10 Мастер-линия для устройств типа датчиков
            if(dev->getType() == TypeObject::PLUGGABLE_TO2WIRE){
                textObject["masterLine"] = QString::number(dev->getMasterLineNum());
            }
            else if(dev->getType() == TypeObject::PLUGGABLE_TO485){
                textObject["masterLine"] = "none";
            }

///формируем массив
            textsArray.append(textObject);

        }
    }
    fsaverPrivate->m_currentJsonObject["dev_description"] = textsArray;
    textsArray = QJsonArray();

    ///---------------------------------------------------------------------------
    ///---------------------------------------------------------------------------
    /// -------------вытаскиваем всю информацию о линиях связи--------------------
        QListIterator<ConnectionLine*> itl(manager.getLines());
        if(!manager.getLines().isEmpty()){
            while(itl.hasNext()){
                ConnectionLine * line = itl.next();
                QJsonObject textObject;

    ///2.1. Системный ID линии
                textObject["line_id"] = QString::number(line->getId());

    ///2.2 Удалена пользователем
                textObject["line_removed"] = QVariant(line->isRemoved()).toString();

    ///2.3 Пользовательский ID
                textObject["line_user_id"] = QString::number(line->getUserId());

    ///2.4 Вытаскиваем все точки, по которым строится линия

                QString points;
                QListIterator<QPoint> itp (line->getKeyPointsList() );

                if(!line->getKeyPointsList().isEmpty()){
                    while(itp.hasNext()){
                        QPoint p = itp.next();
                               points.append(QString::number(p.x())).
                               append(",").
                               append(QString::number(p.y())).
                               append(";");
                    }

                }
                textObject["line_points"] = points;

    ///2.5 Вытаскиваем ID устройств, которые включены в эту линию
                QString notifierId;
                QListIterator<Devices*> itd(line->getSubscribers());
                while(itd.hasNext()){
                    notifierId.append(QString::number(itd.next()->getId()));
                    if(itd.hasNext()){
                        notifierId.push_back(",");
                    }
                }
                textObject["notifiers"] = notifierId;

   ///2.6 Линия контроллеров или линия датчиков
               switch (line->getRole()) {
               case LineRole::RS485LINE:
                   textObject["linerole"] = "rs485line";
                   break;
               case LineRole::DUALWIRELINE:
                   textObject["linerole"] = "dualwire";
                   break;
               default:
                   break;
               }
    ///2.7 Подсистема
               switch (line->getSubSystem()) {
               case SubSystem::FIRE:
                   textObject["subsystem"] = "fire";
                   break;
               case SubSystem::SKUD:
                   textObject["subsystem"] = "skud";
                   break;
               default:
                   break;
               }

     ///2.8 мастер-линия
               if(line->getRole() == LineRole::DUALWIRELINE){
                   textObject["masterLine"] = QString::number(line->getMasterLineNum());
               }
               else if(line->getRole() == LineRole::RS485LINE){
                   textObject["masterLine"] = "none";
               }

    ///формируем массив
                textsArray.append(textObject);
            }
        }
   fsaverPrivate->m_currentJsonObject["line_description"] = textsArray;
}
