#include "dugraphicsscene.h"
#include "DuGlobalDefines.h"
#include "duthreadtimer.h"
#include "duballitem.h"
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
    mPlatformItem->move(event->key());
}

void DuGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    event->accept();
}

void DuGraphicsScene::createObjects()
{
    mThreadTimer = new DuThreadTimer(MILISECONDS, this);
    mBallItem = new DuBallItem(XBALL, YBALL, HBALL, VXBALL, VYBALL);
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
    // LÓGICA DO JOGO

    mBall->move();
    if(mBallItem->collidesWith(mPlatform)){

    }
    update();
}
