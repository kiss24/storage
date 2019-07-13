#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDateTime>

struct CommodityInfo{
    int ID;
    int type;
    int count;
    double price;
    double totalPrice;
    QString time;
    QString category;
    QString company;
    QString note;
};

class Common
{
public:
    Common();
};

#endif // COMMON_H
