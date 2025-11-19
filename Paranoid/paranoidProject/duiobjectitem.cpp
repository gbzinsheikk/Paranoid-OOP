#include "duiobjectitem.h"

DuIObjectItem::DuIObjectItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    mx = x;
    my = y;
    mw = w;
    mh = h;
    mvx = vx;
    mvy = vy;

    // Define a posição inicial do item na cena
    setPos(mx, my);
}

void DuIObjectItem::move()
{
    mx += mvx;
    my += mvy;

    // Atualiza a posição na cena
    setPos(mx, my);
}

QRectF DuIObjectItem::boundingRect() const
{
    // Retorna o retângulo começando em 0,0.
    // A posição (x,y) já é controlada pelo setPos.
    return QRectF(0, 0, mw, mh);
}
