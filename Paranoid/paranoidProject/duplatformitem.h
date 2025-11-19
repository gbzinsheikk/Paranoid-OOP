#ifndef DUPLATFORMITEM_H
#define DUPLATFORMITEM_H

#include "duiobjectitem.h"

class DuPlatformItem : public DuIObjectItem
{
public:
    DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);

    //DuPlatformItem::DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent)
    void move(int key);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // DUPLATFORMITEM_H
