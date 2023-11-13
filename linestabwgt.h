#ifndef TABWGT_H
#define TABWGT_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVector>

class LinesTabWgt: public QWidget
{
    Q_OBJECT
public:
    explicit LinesTabWgt(QWidget *parent = 0);
    ~LinesTabWgt();

private:
    QVector<QPushButton*> v_bn;
    QVBoxLayout * groupLayout = nullptr;
    QVBoxLayout * mainlayout = nullptr;
    QHBoxLayout * row1 = nullptr;
    QHBoxLayout * row2 = nullptr;
    QPushButton * bnBigLine = nullptr;
    QLabel * label1 = nullptr;
    QPushButton * bnSmallLine = nullptr;
    QLabel * label2 = nullptr;
    QGroupBox * groupbox = nullptr;

    //
    QGroupBox * createGroup();

public:
    QPushButton *getBigLineBn() const;
    QPushButton *getSmallLineBn() const;

    void setCheckedAllBns(bool checked);
    void setEnabledAllBns(bool enabled);

};

#endif // TABWGT_H
