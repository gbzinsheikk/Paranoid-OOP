#ifndef DUBLOCKITEM_H
#define DUBLOCKITEM_H

#include <QColor>
#include <vector>

class duBlockItem {
protected:
    int dureza;
    int hits;
    std::vector<QColor> cores;
    QColor corAtual;

public:
    duBlockItem(int dureza_,int x, int y, int w, int h,const std::vector<QColor>& cores_);
    virtual ~duBlockItem();

    bool atingir();
    void updateColor();
    bool isBroken() const;

    QColor getCor() const;
};

#endif // DUBLOCKITEM_H
