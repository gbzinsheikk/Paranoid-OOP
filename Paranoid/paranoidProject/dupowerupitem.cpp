#include "dupowerupitem.h"
//#include "DuGlobalDefines.h"
//#include "duutil.h"

#include <QPainter>
#include <QKeyEvent>

DuPowerUpItem::DuPowerUpItem(int x, int y, int w, int h, int vx, int vy, PowerUpType type, QGraphicsItem *parent)
    : DuIObjectItem(x, y, w, h, vx, vy, 0, parent)
{
    mType = type;
}
/*
void DuPowerUpItem::collected()
{

}
*/
/*
void DuPowerUpItem::move()
{

}
*/

void DuPowerUpItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Cores diferentes para cada tipo
    if (mType == POWERUP_MULTIBALL) {
        painter->setBrush(Qt::yellow);
    } else if (mType == POWERUP_EXPAND_PLATFORM) {
        painter->setBrush(Qt::blue);  // Azul claro para expandir plataforma
    }

    painter->drawRect(0, 0, mw, mh);

    // Opcional: Adicionar símbolo visual
    painter->setPen(QPen(Qt::black, 2));
    if (mType == POWERUP_MULTIBALL) {
        // Desenhar 3 círculos pequenos
        painter->drawEllipse(3, 3, 5, 5);
        painter->drawEllipse(12, 3, 5, 5);
        painter->drawEllipse(7, 10, 5, 5);
    } else if (mType == POWERUP_EXPAND_PLATFORM) {
        // Desenhar setas para fora (←→)
        painter->drawLine(3, 10, 8, 10);
        painter->drawLine(3, 10, 5, 8);
        painter->drawLine(3, 10, 5, 12);

        painter->drawLine(17, 10, 12, 10);
        painter->drawLine(17, 10, 15, 8);
        painter->drawLine(17, 10, 15, 12);
    }
}


