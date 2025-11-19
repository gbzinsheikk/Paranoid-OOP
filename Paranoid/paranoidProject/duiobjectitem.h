#ifndef DUIOBJECTITEM_H
#define DUIOBJECTITEM_H
#include <QGraphicsItem>

class DuIObjectItem : public QGraphicsItem
{
public:
    DuIObjectItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent = nullptr);

    void setx(int x) { mx=x; }
    void sety(int y) { mx=y; }
    void setw(int w) { mx=w; }
    void seth(int h) { mx=h; }
    void setvx(int vx) { mx=vx; }
    void setvy(int vy) { mx=vy; }

    int getx() const { return mx; }
    int gety() const { return my; }
    int getw() const { return mw; }
    int geth() const { return mh; }
    int gevx() const { return mvx; }
    int gevy() const { return mvy; }

    virtual void move();

protected:
    QRectF boundingRect() const override;

    int mx, my;
    int mw, mh;
    int mvx, mvy;

};

#endif // DUIOBJECTITEM_H
