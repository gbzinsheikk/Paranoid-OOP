#include "duplatformitem.h"
#include "DuGlobalDefines.h"
//#include "duutil.h"
#include <QPainter>
#include <QKeyEvent>

DuPlatformItem::DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent)
    : DuIObjectItem(x, y, w, h, vx, vy, parent)
{
    // Inicializa variáveis
    mIsLeftPressed = false;
    mIsRightPressed = false;
    mCurrentVx = 0.0;
}

void DuPlatformItem::keyPress(int key)
{
    if (key == Qt::Key_Left) mIsLeftPressed = true;
    if (key == Qt::Key_Right) mIsRightPressed = true;
}

void DuPlatformItem::keyRelease(int key)
{
    if (key == Qt::Key_Left) mIsLeftPressed = false;
    if (key == Qt::Key_Right) mIsRightPressed = false;
}

void DuPlatformItem::move()
{
    // Aceleração
    if (mIsLeftPressed) {
        // Acelera para a esquerda (negativo)
        if (mCurrentVx > -VXPLATFORM)
            mCurrentVx -= PLATFORM_ACCEL;
    }
    else if (mIsRightPressed) {
        // Acelera para a direita (positivo)
        if (mCurrentVx < VXPLATFORM)
            mCurrentVx += PLATFORM_ACCEL;
    }
    // Interpolação
    else {
        if (mCurrentVx > 0) {
            mCurrentVx -= PLATFORM_FRIC;
            if (mCurrentVx < 0) mCurrentVx = 0;
        } else if (mCurrentVx < 0) {
            mCurrentVx += PLATFORM_FRIC;
            if (mCurrentVx > 0) mCurrentVx = 0;
        }
    }

    // Aplicação do Movimento
    mx += (int)mCurrentVx;

    // Limites da Tela
    if (mx < 0) {
        mx = 0;
        mCurrentVx = 0;
    } else if (mx > (XSIZE - WPLATFORM)) {
        mx = XSIZE - WPLATFORM;
        mCurrentVx = 0;
    }

    // Atualiza na tela
    setPos(mx, my);
}

void DuPlatformItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(0, 0, mw, mh);
}
