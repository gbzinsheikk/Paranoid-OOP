#ifndef DUBLOCKITEM_H
#define DUBLOCKITEM_H

#include "duiobjectitem.h"
#include <QColor>
#include <vector>

class duBlockItem : public DuIObjectItem {
public:
    duBlockItem(int dureza, int x, int y, int w, int h, QColor color, QGraphicsItem *parent = nullptr);

    bool atingir();
    bool isBroken() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,  QWidget *widget = 0) override;

private:
    int mDureza;
    int mHits;
    QColor mCorAtual;

    void atualizarCor();
};

#endif // DUBLOCKITEM_H
