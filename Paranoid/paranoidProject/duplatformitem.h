#ifndef DUPLATFORMITEM_H
#define DUPLATFORMITEM_H

#include "duiobjectitem.h"

class DuPlatformItem : public DuIObjectItem
{
public:
    DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);

    // Captura o estado das teclas
    void keyPress(int key);
    void keyRelease(int key);

    void move();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    // Flags
    bool mIsLeftPressed;
    bool mIsRightPressed;

    // Velocidade atual
    double mCurrentVx;
};

#endif // DUPLATFORMITEM_H
