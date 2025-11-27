#include "dupowerupitem.h"
#include "DuGlobalDefines.h"
//#include "duutil.h"

#include <QPainter>
#include <QKeyEvent>

DuPowerUpItem::DuPowerUpItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent)
    : DuIObjectItem(x, y, w, h, vx, vy, 0, parent)
{

}

void DuPowerUpItem::collected()
{

}
/*
void DuPowerUpItem::move()
{

}
*/
void DuPowerUpItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::yellow);
    painter->drawRect(0, 0, mw, mh);
}
