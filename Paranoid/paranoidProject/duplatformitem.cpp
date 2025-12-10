#include "duplatformitem.h"
#include "DuGlobalDefines.h"
//#include "duutil.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>

DuPlatformItem::DuPlatformItem(int x, int y, int w, int h, int vx, int vy, QGraphicsItem *parent)
    : DuIObjectItem(x, y, w, h, vx, vy, 0, parent)
{

    mIsLeftPressed = false;
    mIsRightPressed = false;
    mCurrentVx = 0.0;
    mIsExpanded = false;
    mOriginalWidth = w;
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

void DuPlatformItem::expandPlatform()
{
    if (!mIsExpanded) {
        // Centraliza a expansão (expande igualmente para ambos os lados)
        int widthDiff = WPLATFORM_EXPANDED - mw;
        mx -= widthDiff / 2;  // Move para esquerda metade da diferença

        // Verifica limites
        if (mx < 0) mx = 0;
        if (mx > (XSIZE - WPLATFORM_EXPANDED)) mx = XSIZE - WPLATFORM_EXPANDED;

        mw = WPLATFORM_EXPANDED;
        mIsExpanded = true;

        setPos(mx, my);
        prepareGeometryChange();  // Importante: notifica mudança de tamanho
    }
    // Se já está expandida, não faz nada (mantém expandida)
}

void DuPlatformItem::resetPlatformSize()
{
    if (mIsExpanded) {
        // Centraliza a redução
        int widthDiff = mw - mOriginalWidth;
        mx += widthDiff / 2;

        mw = mOriginalWidth;
        mIsExpanded = false;

        setPos(mx, my);
        prepareGeometryChange();  // Importante: notifica mudança de tamanho
    }
}


void DuPlatformItem::move()
{
    /* Aceleração */
    if (mIsLeftPressed) {
        // Esquerda (negativo)
        if (mCurrentVx > -VXPLATFORM)
            mCurrentVx -= PLATFORM_ACCEL;
    }
    else if (mIsRightPressed) {
        // Direita (positivo)
        if (mCurrentVx < VXPLATFORM)
            mCurrentVx += PLATFORM_ACCEL;
    }
    /* Interpolação */
    else {
        if (mCurrentVx > 0) {
            mCurrentVx -= PLATFORM_FRIC;
            if (mCurrentVx < 0) mCurrentVx = 0;
        } else if (mCurrentVx < 0) {
            mCurrentVx += PLATFORM_FRIC;
            if (mCurrentVx > 0) mCurrentVx = 0;
        }
    }

    /* Aplicação do Movimento */
    mx += (int)mCurrentVx;

    /* Limites da Tela */
    if (mx < 0) {
        mx = 0;
        mCurrentVx = 0;
    } else if (mx > (XSIZE - mw)) {
        mx = XSIZE - mw;
        mCurrentVx = 0;
    }

    setPos(mx, my);
}

void DuPlatformItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(0, 0, mw, mh);
}
