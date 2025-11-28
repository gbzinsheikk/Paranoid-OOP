#ifndef DUIOBJECTITEM_H
#define DUIOBJECTITEM_H

#include <QGraphicsItem>

class DuIObjectItem : public QGraphicsItem
{
public:
    DuIObjectItem(int x, int y, int w, int h, float vx, float vy, int score, QGraphicsItem *parent = nullptr);

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
    float getvx() const { return mvx; }
    float getvy() const { return mvy; }

    void setscore(int score) { mscore=score; }
    int getScore() const {return mscore;};

    virtual void move();

protected:
    QRectF boundingRect() const override;

    int mx, my;
    int mw, mh;
    float mvx, mvy;
    float mscore;

};

#endif // DUIOBJECTITEM_H
