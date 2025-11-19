#ifndef DUIOBJECTITEM_H
#define DUIOBJECTITEM_H
#include <QGraphicsItem>

class DuIObjectItem : public QGraphicsItem
{
public:
    DuIObjectItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);

    void setx(int x) { mx=x; }
    void sety(int y) { my=y; }
    void setw(int w) { mw=w; }
    void seth(int h) { mh=h; }
    void setvx(int vx) { mvx=vx; }
    void setvy(int vy) { mvy=vy; }

    int getx() const { return mx; }
    int gety() const { return my; }
    int getw() const { return mw; }
    int geth() const { return mh; }
    int getvx() const { return mvx; }
    int getvy() const { return mvy; }

    virtual void move();

protected:
    QRectF boundingRect() const override;

    int mx, my;
    int mw, mh;
    int mvx, mvy;

};

#endif // DUIOBJECTITEM_H
