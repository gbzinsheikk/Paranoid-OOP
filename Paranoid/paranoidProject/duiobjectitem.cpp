#include "duiobjectitem.h"

DuIObjectItem::DuIObjectItem(int x, int y, inw w, int h, int vx, int vy, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    mx = x;
    my = y;
    mw = w;
    mh = h;
    mvx = vx;
    mvy = vy;
}

void DuIObjectItem::move()
{
    mx += mvx;
    my += mvy;
}

QRectF DuIObjectItem::boundingRect() const
{
    return QrectF(mx, my, mw, mh);
}
