#include "dublockitem.h"
#include <QPainter>

duBlockItem::duBlockItem(int dureza, int x, int y, int w, int h, QColor color, QGraphicsItem *parent)
    : DuIObjectItem(x, y, w, h, 0, 0, 100, parent)
{
    mDureza = dureza;
    mHits = 0;
    mCorAtual = color;

    atualizarCor();
}

void duBlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::black);
    painter->setBrush(mCorAtual);
    painter->drawRect(0, 0, mw, mh);
}

bool duBlockItem::atingir() {
    mHits++;
    atualizarCor();
    return isBroken();
}

bool duBlockItem::isBroken() const {
    return mHits >= mDureza;
}

void duBlockItem::atualizarCor() {

    int vidaRestante = mDureza - mHits;

    if (vidaRestante >= 3) mCorAtual = Qt::green;
    else if (vidaRestante == 2) mCorAtual = Qt::yellow;
    else if (vidaRestante == 1) mCorAtual = Qt::red;
}
