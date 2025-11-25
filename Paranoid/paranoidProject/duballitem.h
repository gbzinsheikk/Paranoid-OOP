#ifndef DUBALLITEM_H
#define DUBALLITEM_H

#include "duiobjectitem.h"

class DuBallItem : public DuIObjectItem
{
public:
    DuBallItem(int x, int y, int w, int h, int vx, int vy, int score, QGraphicsItem *parent = nullptr);
    void move() override;
    int getScore() const { return (int)mscore; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};

#endif // DUBALLITEM_H
