#ifndef DUPOWERUPITEM_H
#define DUPOWERUPITEM_H

#include "duiobjectitem.h"

enum PowerUpType {
    POWERUP_MULTIBALL,
    POWERUP_EXPAND_PLATFORM
};


class DuPowerUpItem : public DuIObjectItem
{
public:
    DuPowerUpItem(int x, int y, int w, int h, int vx, int vy,PowerUpType type = POWERUP_MULTIBALL ,QGraphicsItem *parent = nullptr);
    //void collected();
    //void move();
    PowerUpType getType() const { return mType; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    PowerUpType mType;
};

#endif // DUPOWERUPITEM_H
