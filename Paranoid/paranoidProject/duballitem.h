#ifndef DUBALLITEM_H
#define DUBALLITEM_H
#include "duiobjectitem.h".h"

class DuBallItem : public DuIObjectItem
{
public:
    DuBallItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);
    void move() override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};

#endif // DUBALLITEM_H
