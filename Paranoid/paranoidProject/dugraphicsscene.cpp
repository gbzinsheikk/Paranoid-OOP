#include "dugraphicsscene.h"
#include "DuGlobalDefines.h"
#include "duthreadtimer.h"
#include "duballitem.h"
#include "duutil.h"
#include "duplatformitem.h"
#include "dupowerupitem.h"
#include "dublockitem.h"
#include <QRandomGenerator>

#include <QKeyEvent>

DuGraphicsScene::DuGraphicsScene(QObject *parent) : QGraphicsScene(0.0 , 0.0, XSIZE, YSIZE, parent)
{
    mTotalScore = 0;

    xmin = 20;
    xmax = 400;

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
    xrandomNumber = QRandomGenerator::global()->bounded(xmin, xmax);
    DuBallItem* newBall = new DuBallItem(xrandomNumber, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f, Qt::green);
    addItem(newBall);
    mBallList.append(newBall);

    // Limpa paredes extras

    // for(QGraphicsItem* wall : mWallList) {
    //     removeItem(wall);
    //     delete wall;
    // }
    // mWallList.clear();

    // Recria paredes iniciais
    // xrandomNumber = QRandomGenerator::global()->bounded(xmin, xmax);
    // QGraphicsRectItem* block = addRect(xrandomNumber, 100, 300, 50, QPen(Qt::black), QBrush(Qt::white));
    // mWallList.append(block);

    /*
    QGraphicsRectItem* block2 = addRect(350, 100, 150, 50, QPen(Qt::black), QBrush(Qt::white));
    mWallList.append(block2);
    */

    mPlatformItem->setx(XPLATFORM);
    mPlatformItem->sety(YPLATFORM);
    mPlatformItem->setvx(VXPLATFORM);
    mPlatformItem->setPos(XPLATFORM, YPLATFORM);
    //mPlatformItem->mCurrentVx(0);

    xrandomNumber = QRandomGenerator::global()->bounded(xmin, xmax);
    mPowerUpItem->setx(xrandomNumber);
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
    xrandomNumber = QRandomGenerator::global()->bounded(xmin, xmax);
    DuBallItem* firstBall = new DuBallItem(xrandomNumber, YBALL, WBALL, HBALL, VXBALL, VYBALL, 0.0f, Qt::green);
    mBallList.append(firstBall);
    mPlatformItem = new DuPlatformItem(XPLATFORM, YPLATFORM, WPLATFORM, HPLATFORM, VXPLATFORM, VYPLATFORM);
    xrandomNumber = QRandomGenerator::global()->bounded(xmin, xmax);
    mPowerUpItem = new DuPowerUpItem(xrandomNumber, YPWRUP, WPWRUP, HPWRUP, VXPWRUP, VYPWRUP);
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

    // QGraphicsRectItem* wall = addRect(0, 100, 150, 50, QPen(Qt::black), QBrush(Qt::white));
    // mWallList.append(wall);

    // QGraphicsRectItem* wall2 = addRect(350, 100, 150, 50, QPen(Qt::black), QBrush(Qt::white));
    // mWallList.append(wall2);

    // duBlockItem* block : mBlockList;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {

            int x = 50 + (i * 80);
            int y = 50 + (j * 40);
            int vida = 3 - j;

            duBlockItem* newBlock = new duBlockItem(vida, x, y, 70, 30, Qt::green);

            // Adiciona na Cena E na Lista
            addItem(newBlock);
            mBlockList.append(newBlock);
        }
    }

}
void DuGraphicsScene::connectObjects()
{
    connect(mThreadTimer, &DuThreadTimer :: timeOut, this, &DuGraphicsScene :: updateScene);
}

void DuGraphicsScene::updateScene()
{
    mPlatformItem->move();
    mPowerUpItem->move();

    /* LÓGICA DA BOLA ANTIGA (P/ APENAS UMA BOLA) */

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

        // Checa colisão com os bricks
        for (int j = mBlockList.size() - 1; j >= 0; --j) {
            duBlockItem* block = mBlockList[j];

            if (ball->collidesWithItem(block)) {
                /*
                ball->setvy(-ball->getvy());
                removeItem(brick);
                mBrickList.removeAt(j);
                delete brick;
                mTotalScore += 100;
                */

                QRectF ballRect = ball->sceneBoundingRect();
                QRectF wallRect = block->sceneBoundingRect();

                // Calcula o retângulo da área da interseção
                QRectF intersection = ballRect.intersected(wallRect);

                // Se a interseção é mais larga que alta -> Inverte Y
                if (intersection.width() > intersection.height()) {
                    ball->setvy(-ball->getvy());
                }
                // Se a interseção é mais alta que larga -> Inverte X
                else {
                    ball->setvx(-ball->getvx());
                }

                /*
                removeItem(wall);
                mBrickList.removeAt(j);
                delete wall;
                mTotalScore += 100;
                */

                bool quebrou = block->atingir();

                // Verifica se deve destruir
                if (quebrou) {

                    removeItem(block);
                    mBlockList.removeAt(j);
                    mTotalScore += 100; // Ou block->getScore()
                    delete block;
                }
                else {
                    // Se não quebrou, ele mudou de cor
                    block->update();
                }
                break;
            }
        }

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

    // Atualiza Score/Speed baseado na primeira bola
    else {
        emit scoreChanged(mTotalScore);
        //emit speedChanged(DuUtil::abs(mBallList.first()->getvy()));
        DuBallItem* b = mBallList.first();
        float speedX = DuUtil::abs(b->getvx());
        float speedY = DuUtil::abs(b->getvy());
        float realSpeed = (speedX > speedY) ? speedX : speedY;

        emit speedChanged(realSpeed);
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

    //for(int i = 0; i < 2; i++) {

        // Cria nova(s) bola(s)
        DuBallItem* newBall = new DuBallItem(xrandomNumber, (YPLATFORM-10), WBALL, HBALL, VXBALL, -VYBALL, 0.0f, Qt::yellow);
        addItem(newBall);
        mBallList.append(newBall);

        DuBallItem* newBall2 = new DuBallItem((xrandomNumber-20), (YPLATFORM-30), WBALL, HBALL, -VXBALL, -VYBALL, 0.0f, Qt::yellow);
        addItem(newBall2);
        mBallList.append(newBall2);

        // [...]
    //}
}

