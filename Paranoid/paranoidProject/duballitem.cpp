#include "duballitem.h"
#include "DuGlobalDefines.h"
#include <QPainter>

DuBallItem::DuBallItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent) : DuIObjectItem(x, y, w, h, vx, vy, parent)
{

}

void DuBallItem::move()
{
    if(mx < 0 || mx > (XSIZE - WBALL)){
        mvx = -mvx;
    }
    if (my < 0 || my > (YSIZE - HBALL)){
        mvy = -mvy;
    }
    DuIObjectItem::move();
}

void DuBallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(0, 0, mw, mh);
}
