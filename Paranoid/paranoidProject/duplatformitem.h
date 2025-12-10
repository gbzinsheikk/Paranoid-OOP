#ifndef DUPLATFORMITEM_H
#define DUPLATFORMITEM_H

#include "duiobjectitem.h"

class DuPlatformItem : public DuIObjectItem
{
public:
    DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);

    /* Captura o estado das teclas */
    void keyPress(int key);
    void keyRelease(int key);
    void move();
    void expandPlatform();
    void resetPlatformSize();
    bool isExpanded() const { return mIsExpanded; }

    /* Velocidade atual */
    double mCurrentVx;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    bool mIsLeftPressed;
    bool mIsRightPressed;
    bool mIsExpanded;
    int mOriginalWidth;
};

#endif // DUPLATFORMITEM_H
