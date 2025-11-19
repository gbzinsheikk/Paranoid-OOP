#include "duballitem.h"
#include "DuGlobalDefines.h"
#include "duutil.h"
#include <QPainter>

DuBallItem::DuBallItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent) : DuIObjectItem(x, y, w, h, vx, vy, parent)
{

}

void DuBallItem::move()
{
    // Colisão com Paredes Laterais
    if(mx <= 0 || mx >= (XSIZE - WBALL)){

        // Aceleração Linear: Aumenta 1 se ainda não chegou no máximo
        if(DuUtil::abs(mvx) < MAX_SPEED){
            if(mvx > 0) mvx++; else mvx--;
        }

        // Inversão
        mvx = -mvx;

        // Evita que a bola "grude" na parede se estiver muito rápida
        if(mx <= 0) mx = 1;
        else mx = XSIZE - WBALL - 1;
    }

    // Colisão com Topo
    // Não há colisão com o fundo (YSIZE) porque é Game Over (falta implementar)
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
    // Se bater no fundo, apenas inverte por enquanto (sem acelerar)
    else if (my >= (YSIZE - HBALL)) {
        mvy = -mvy;
        my = YSIZE - HBALL - 1;
    }

    // Move a bola logicamente e atualiza a tela
    DuIObjectItem::move(); // Atualiza mx e my baseados no novo mvx/mvy
    setPos(mx, my);        // Atualiza o visual
}

void DuBallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(0, 0, mw, mh);
}
