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
    mTotalScore = 0;

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

    /*
    mBallItem->setx(XBALL);
    mBallItem->sety(YBALL);
    mBallItem->setvx(VXBALL);
    mBallItem->setvy(VYBALL);
    mBallItem->setPos(XBALL, YBALL);
    */

    mTotalScore = 0;
    emit scoreChanged(mTotalScore);

    // Limpa bolas extras
    for(DuBallItem* ball : mBallList) {
        removeItem(ball);
        delete ball;
    }
    mBallList.clear();

    // Recria a bola inicial
    DuBallItem* newBall = new DuBallItem(XBALL, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f, Qt::green);
    addItem(newBall);
    mBallList.append(newBall);

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
    mPowerUpItem->show();

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
    //mBallItem = new DuBallItem(XBALL, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f);
    DuBallItem* firstBall = new DuBallItem(XBALL, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f, Qt::green);
    mBallList.append(firstBall);
    mPlatformItem = new DuPlatformItem(XPLATFORM, YPLATFORM, WPLATFORM, HPLATFORM, VXPLATFORM, VYPLATFORM);
    mPowerUpItem = new DuPowerUpItem(XPWRUP, YPWRUP, WPWRUP, HPWRUP, VXPWRUP, VYPWRUP);
}

void DuGraphicsScene::configureObjects()
{
    //addItem(mBallItem);
    for(DuBallItem* ball : mBallList) {
        addItem(ball);
    }
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
    mPlatformItem->move();
    mPowerUpItem->move();

    /* LÓGICA DA BOLA ANTIGA */

        //mBallItem->move();

        /* Atualiza Score */

        //emit scoreChanged(mBallItem->getScore());

        /* Atualiza Barra Velocidade */

        //int currentSpeedY = DuUtil::abs(mBallItem->getvy());
        //emit speedChanged(currentSpeedY);

        /* GAME OVER */

        // Verifica se a posição Y da bola passou do limite inferior
        //if (mBallItem->gety() >= (YSIZE - (HBALL-50))) {
        //    stopScene();     // Para o Timer
        //    emit gameOver(); // Emite sinal GAME OVER
        //}

        //if(mBallItem->collidesWithItem(mPlatformItem)){
        //    checkCollisions();
        //}

        //if(mPowerUpItem->collidesWithItem(mPlatformItem)){
            // Coleta PowerUp
        //    collectedPwrUp();
        //}

    /* LÓGICA DA(S) BOLA(S) */

    for (int i = 0; i < mBallList.size(); ++i) {
        DuBallItem* ball = mBallList[i];
        ball->move();

        int pointsEarned = ball->getScore();

        if (pointsEarned > 0) {
            mTotalScore += pointsEarned;
            ball->setscore(0);
        }

        // Checa colisão com a plataforma
        if(ball->collidesWithItem(mPlatformItem)){
            checkCollisions(ball);
        }

        // Checa GAME OVER (individual)
        if (ball->gety() >= (YSIZE - (HBALL-50))) {
            removeItem(ball);
            mBallList.removeAt(i);
            delete ball;
            i--;
        }
    }

    // Se a lista ficou vazia -> GAME OVER REAL
    if (mBallList.isEmpty()) {
        stopScene();
        emit gameOver();
    }

    // Senão, atualiza Score/Speed baseado na primeira bola
    else {
        emit scoreChanged(mTotalScore);
        emit speedChanged(DuUtil::abs(mBallList.first()->getvy()));
    }

    // Lógica PowerUp
    if(mPowerUpItem->isVisible() && mPowerUpItem->collidesWithItem(mPlatformItem)){
        collectedPwrUp();
    }

    update();
}

void DuGraphicsScene::checkCollisions(DuBallItem* ball)
{
    //int bvx = mBallItem->getvx();
    //int bvy = mBallItem->getvy();

    int bvx = ball->getvx();
    int bvy = ball->getvy();

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
        //mBallItem->setvx(bvx);
        //mBallItem->setvy(bvy);
        ball->setvx(bvx);
        ball->setvy(bvy);
}

void DuGraphicsScene::collectedPwrUp()
{   
    mPowerUpItem->hide();
    mPowerUpItem->setPos(-1000, -1000);

    for(int i = 0; i < 2; i++) {

        // Cria nova(s) bola(s)
        DuBallItem* newBall = new DuBallItem(XPLATFORM, (YPLATFORM-10), WBALL, HBALL, VXBALL, -VYBALL, 0.0f, Qt::yellow);
        addItem(newBall);
        mBallList.append(newBall);

        DuBallItem* newBall2 = new DuBallItem((XPLATFORM-30), (YPLATFORM-30), WBALL, HBALL, -VXBALL, +VYBALL, 0.0f, Qt::yellow);
        addItem(newBall2);
        mBallList.append(newBall2);

        // [...]
    }
}

