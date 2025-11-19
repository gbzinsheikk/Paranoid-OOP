#include "duplatformitem.h"
#include "DuGlobalDefines.h"
#include "duutil.h"
#include <QPainter>
#include <QKeyEvent>

DuPlatformItem::DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent) : DuIObjectItem(x, y, w, h, vx, vy, parent)
{

}

void DuPlatformItem::move(int key)
{
    if(key == Qt::Key_Left && mx > 0) {
        mx -= DuUtil::abs(mvx); // Subtrai a velocidade para ir à ESQUERDA
        //DuIObjectItem::move();
    } else if (key == Qt::Key_Right && mx < (XSIZE - WPLATFORM)) {
        mx += DuUtil::abs(mvx); // Soma a velocidade para ir à DIREITA
        //DuIObjectItem::move();
    }
    // Atualiza a posição visual do item na cena
    setPos(mx, my);

}

void DuPlatformItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::blue); // Cor
    // Desenha em 0,0. A posição na tela é dada pelo setPos.
    painter->drawRect(0, 0, mw, mh);
}
