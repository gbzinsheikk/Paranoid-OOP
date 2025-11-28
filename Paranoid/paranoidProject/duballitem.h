#ifndef DUBALLITEM_H
#define DUBALLITEM_H

#include "duiobjectitem.h"

#include <QColor>

class DuBallItem : public DuIObjectItem
{
public:
    DuBallItem(int x, int y, int w, int h, float vx, float vy, int score, QColor color = Qt::green, QGraphicsItem *parent = nullptr);
    void move() override;
    //int getScore() const { return (int)mscore; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
    QColor mColor;
};

#endif // DUBALLITEM_H
