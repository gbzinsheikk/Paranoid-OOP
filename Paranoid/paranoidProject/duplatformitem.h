#ifndef DUPLATFORMITEM_H
#define DUPLATFORMITEM_H

#include "duiobjectitem.h"

class DuPlatformItem
{
public:
    DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);
    void move(int key);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};

#endif // DUPLATFORMITEM_H
