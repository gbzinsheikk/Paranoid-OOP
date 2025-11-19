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
    mPlatformItem->move(event->key());
}

void DuGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    event->accept();
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
    if(mBallItem->collidesWithItem(mPlatformItem)){
        checkCollisions();
    }
    update();
}

void DuGraphicsScene::checkCollisions()
{
    int bvx = mBallItem->getvx();
    int bvy = mBallItem->getvy();
    const int pvx = mPlatformItem->getvx();
    const int pvy = mPlatformItem->getvy();
    if(bvx > 0 && bvy > 0 && pvx > 0 && pvy ==0){
        bvx += DuUtil::abs(bvx);
        bvy -= DuUtil::abs(bvy);
    } else if(bvx < 0 && bvy > 0 && pvx > 0 && pvy ==0){
        bvx -= DuUtil::abs(bvx);
        bvy += DuUtil::abs(bvy);
    } else if(bvx > 0 && bvy > 0 && pvx < 0 && pvy ==0){
        bvx += DuUtil::abs(bvx);
        bvy -= DuUtil::abs(bvy);
    } else if(bvx < 0 && bvy > 0 && pvx < 0 && pvy ==0){
        bvx -= DuUtil::abs(bvx);
        bvy -= DuUtil::abs(bvy);
    }
    mBallItem->setvx(bvx);
    mBallItem->setvy(bvy);
}

