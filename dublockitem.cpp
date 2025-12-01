#include "dublockitem.h"
#include <algorithm>
/*
duBlockItem::duBlockItem(int dureza_, const std::vector<QColor>& cores_ : dureza(dureza_), hits(0), cores(cores_)
{
    if (!cores.empty())
        corAtual = cores[0];
}*/

duBlockItem::~duBlockItem() {}

bool duBlockItem::atingir() {
    hits++;
    updateColor();
    return isBroken();
}

void duBlockItem::updateColor() {
    int indice = std::min(hits, (int)cores.size() - 1);
    corAtual = cores[indice];
}

bool duBlockItem::isBroken() const {
    return hits >= dureza;
}

QColor duBlockItem::getCor() const {
    return corAtual;
}

// void DuPlatformItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
// {
//     painter->setBrush(Qt::blue);
//     painter->drawRect(0, 0, mw, mh);
// }


duBlockItem::duBlockItem(int x, int y, int mw, int mh,const std::vector<QColor>& cores_ ,QGraphicsItem *parent)
    : DuIObjectItem(x, y, w, h, vx, vy, 0, parent)
{
    if (!cores.empty())
        corAtual = cores[0];
}

void duBlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::corAtual);
    painter->drawRect(0, 0, mw, mh);
}
