#ifndef FILESAVER_H
#define FILESAVER_H

#include <memory>
#include <QString>


class FileSaver
{
private:
    FileSaver();
    ///pimpl
    class FileSaverPrivate;
    std::unique_ptr<FileSaverPrivate> fsaverPrivate;

public:
    virtual ~FileSaver();
    ///get object
    static FileSaver& instance();
    void saveToFile(QString fname);
    void setBackgroundScheme(QString fname);
    void makeJsonObject();
};





#endif // FILESAVER_H
