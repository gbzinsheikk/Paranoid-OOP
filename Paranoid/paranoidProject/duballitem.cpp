#include "duballitem.h"
#include "DuGlobalDefines.h"
#include "duutil.h"
//#include "mainwindow.h"
//#include "duarkanoid.h"
#include <QPainter>

DuBallItem::DuBallItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent) : DuIObjectItem(x, y, w, h, vx, vy, parent)
{
}

void DuBallItem::move()
{
    /* Colisão Laterais */

        if(mx <= 0 || mx >= (XSIZE - WBALL)){

            // Aceleração Linear
            if(DuUtil::abs(mvx) < MAX_SPEED){
                if(mvx > 0) mvx++; else mvx--;
            }

            // Inversão
            mvx = -mvx;

            if(mx <= 0) mx = 1;
            else mx = XSIZE - WBALL - 1;
        }

    /* Colisão Topo */

        if (my <= 0){

            // Aceleração Linear
            if(DuUtil::abs(mvy) < MAX_SPEED){
                if(mvy > 0) mvy++; else mvy--;
            }

            // Inversão
            mvy = -mvy;

            // Correção de Posição
            my = 1;
        }

    /* Colisão Fundo (Game Over) */

        else if (my >= (YSIZE - HBALL)) {
            //mvy = -mvy;
            //my = YSIZE - HBALL - 1;
            mvx = 0;
            mvy = 0;
        }

    DuIObjectItem::move(); // Atualiza mx e my baseados no novo mvx/mvy
    setPos(mx, my);
}

void DuBallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(0, 0, mw, mh);
}
