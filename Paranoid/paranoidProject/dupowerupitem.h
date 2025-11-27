#ifndef DUPOWERUPITEM_H
#define DUPOWERUPITEM_H

#include "duiobjectitem.h"

class DuPowerUpItem : public DuIObjectItem
{
public:
    DuPowerUpItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);
    void collected();
    //void move();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DUPOWERUPITEM_H
