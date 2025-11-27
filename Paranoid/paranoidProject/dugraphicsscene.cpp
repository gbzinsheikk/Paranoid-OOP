#include "dugraphicsscene.h"
#include "DuGlobalDefines.h"
#include "duthreadtimer.h"
#include "duballitem.h"
#include "duutil.h"
#include "duplatformitem.h"
#include "dupowerupitem.h"

#include <QKeyEvent>

DuGraphicsScene::DuGraphicsScene(QObject *parent) : QGraphicsScene(0.0 , 0.0, XSIZE, YSIZE, parent)
{
    createObjects();
    configureObjects();
    connectObjects();
}

void DuGraphicsScene::startScene()
{
    mThreadTimer->start();
}

void DuGraphicsScene::resetScene()
{
    //stopScene();

    mBallItem->setx(XBALL);
    mBallItem->sety(YBALL);
    mBallItem->setvx(VXBALL);
    mBallItem->setvy(VYBALL);
    mBallItem->setPos(XBALL, YBALL);

    mPlatformItem->setx(XPLATFORM);
    mPlatformItem->sety(YPLATFORM);
    mPlatformItem->setvx(VXPLATFORM);
    mPlatformItem->setPos(XPLATFORM, YPLATFORM);
    //mPlatformItem->mCurrentVx(0);

    mPowerUpItem->setx(XPWRUP);
    mPowerUpItem->sety(YPWRUP);
    mPowerUpItem->setvx(VXPWRUP);
    mPowerUpItem->setvy(VYPWRUP);
    mPowerUpItem->setPos(XPWRUP, YPWRUP);

    update();
}

void DuGraphicsScene::stopScene()
{
    mThreadTimer->terminate();
}

void DuGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    mPlatformItem->keyPress(event->key());
}

void DuGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    mPlatformItem->keyRelease(event->key());
    //event->accept();
}

void DuGraphicsScene::createObjects()
{
    mThreadTimer = new DuThreadTimer(MILISECONDS, this);
    mBallItem = new DuBallItem(XBALL, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f);
    mPlatformItem = new DuPlatformItem(XPLATFORM, YPLATFORM, WPLATFORM, HPLATFORM, VXPLATFORM, VYPLATFORM);
    mPowerUpItem = new DuPowerUpItem(XPWRUP, YPWRUP, WPWRUP, HPWRUP, VXPWRUP, VYPWRUP);
}

void DuGraphicsScene::configureObjects()
{
    addItem(mBallItem);
    addItem(mPlatformItem);
    addItem(mPowerUpItem);
    addRect(0.0, 0.0, XSIZE, YSIZE, QPen(QColor(Qt::black)));
}

void DuGraphicsScene::connectObjects()
{
    connect(mThreadTimer, &DuThreadTimer :: timeOut, this, &DuGraphicsScene :: updateScene);
}

void DuGraphicsScene::updateScene()
{
    mBallItem->move();
    mPlatformItem->move();
    mPowerUpItem->move();

    /* Atualiza Score */

    emit scoreChanged(mBallItem->getScore());

    /* Atualiza Barra Velocidade */

    int currentSpeedY = DuUtil::abs(mBallItem->getvy());
    emit speedChanged(currentSpeedY);

    /* GAME OVER */

    // Verifica se a posição Y da bola passou do limite inferior
    if (mBallItem->gety() >= (YSIZE - (HBALL-50))) {
        stopScene();     // Para o Timer
        emit gameOver(); // Emite sinal GAME OVER
    }

    if(mBallItem->collidesWithItem(mPlatformItem)){
        checkCollisions();
    }

    if(mPowerUpItem->collidesWithItem(mPlatformItem)){
        // Coleta PowerUp
        collectedPwrUp();
    }

    update();
}

void DuGraphicsScene::checkCollisions()
{
    int bvx = mBallItem->getvx();
    int bvy = mBallItem->getvy();

    /* Aceleração Plataforma */

        // Aumenta velocidade Y
        if(DuUtil::abs(bvy) < MAX_SPEED){
            if (bvy > 0) bvy++; else bvy--;
        }

        // Aumenta velocidade X
        /*
        if(DuUtil::abs(bvx) < MAX_SPEED){
            if (bvx > 0) bvx++; else bvx--;
        }
        */

    /* Lógica Bounce */

        // Rebate para cima
        bvy = -DuUtil::abs(bvy);

        // Atualiza a bola
        mBallItem->setvx(bvx);
        mBallItem->setvy(bvy);
}

void DuGraphicsScene::collectedPwrUp()
{
    // Spawna duas novas bolas
    mBallItem = new DuBallItem(XBALL, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f);
    mBallItem = new DuBallItem(XBALL, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f);
    // Deleta PowerUp coletado
    // [***]
}

