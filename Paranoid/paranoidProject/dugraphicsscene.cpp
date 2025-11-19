#include "dugraphicsscene.h"
#include "DuGlobalDefines.h"
#include "duthreadtimer.h"
#include "duballitem.h"
#include "duutil.h"
#include "duplatformitem.h"

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
    mBallItem = new DuBallItem(XBALL, YBALL, WBALL, HBALL, VXBALL, VYBALL);
    mPlatformItem = new DuPlatformItem(XPLATFORM, YPLATFORM, WPLATFORM, HPLATFORM, VXPLATFORM, VYPLATFORM);
}

void DuGraphicsScene::configureObjects()
{
    addItem(mBallItem);
    addItem(mPlatformItem);
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
    if(mBallItem->collidesWithItem(mPlatformItem)){
        checkCollisions();
    }
    update();
}

void DuGraphicsScene::checkCollisions()
{
    int bvx = mBallItem->getvx();
    int bvy = mBallItem->getvy();

    // Aceleração na Plataforma

    // Aumenta a velocidade Y se não atingiu o máximo
    if(DuUtil::abs(bvy) < MAX_SPEED){
        // Se bvy for positivo (descendo), soma 1. Se negativo, subtrai 1.
        if (bvy > 0) bvy++; else bvy--;
    }

    // Opcional: Aumentar velocidade X também?
    /*
    if(DuUtil::abs(bvx) < MAX_SPEED){
        if (bvx > 0) bvx++; else bvx--;
    }
    */

    // Lógica de Rebatida

    // Rebate para cima (Sempre negativo)
    bvy = -DuUtil::abs(bvy);

    // Atualiza a bola
    mBallItem->setvx(bvx);
    mBallItem->setvy(bvy);
}

