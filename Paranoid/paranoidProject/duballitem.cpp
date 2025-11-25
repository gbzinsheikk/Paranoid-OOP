#include "duballitem.h"
#include "DuGlobalDefines.h"
#include "duutil.h"
//#include "mainwindow.h"

#include <QPainter>

DuBallItem::DuBallItem(int x, int y, int w, int h, int vx, int vy, int score, QGraphicsItem *parent) : DuIObjectItem(x, y, w, h, vx, vy, score, parent)
{
}

void DuBallItem::move()
{
    /* Colisão Laterais */

        if(mx <= 0 || mx >= (XSIZE - WBALL)){

            // Aceleração Linear
            if(DuUtil::abs(mvx) < MAX_SPEED){
                if(mvx > 0){
                    mvx++;

                }  else {
                    mvx--;

                }
            }
            // Aumenta Score
            mscore += 25;

            // Inversão
            mvx = -mvx;

            if(mx <= 0) mx = 1;
            else mx = XSIZE - WBALL - 1;
        }

    /* Colisão Topo */

        if (my <= 0){

            // Aceleração Linear
            if(DuUtil::abs(mvy) < MAX_SPEED){
                if(mvy > 0){
                    mvy++;

                }  else {
                    mvy--;

                }
            }            
            // Aumenta Score
            mscore += 500;

            // Inversão
            mvy = -mvy;

            // Correção de Posição
            my = 1;
        }

    /* Colisão Fundo (Game Over) */

        else if (my >= (YSIZE - HBALL)) {
            //mvy = -mvy;
            /*
            my = YSIZE - HBALL - 1;
            mvx = 0;
            mvy = 0;
            */
            mscore = 0;
            //MainWindow::resetButtonOn();
        }

    DuIObjectItem::move();
    setPos(mx, my);
}

void DuBallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(0, 0, mw, mh);
}

