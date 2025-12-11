#include "dugraphicsscene.h"
#include "DuGlobalDefines.h"
#include "duthreadtimer.h"
#include "duballitem.h"
#include "duutil.h"
#include "duplatformitem.h"
#include "dupowerupitem.h"
#include "dublockitem.h"
#include "mainwindow.h"

#include <QRandomGenerator>
#include <QKeyEvent>

DuGraphicsScene::DuGraphicsScene(QObject *parent) : QGraphicsScene(0.0 , 0.0, XSIZE, YSIZE, parent)
{
    mTotalScore = 0;
    mCurrentPhase = 0;
    mCompletedPhases = 0;

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
    mPowerUpItem->hide();
    mPowerUpItem->setPos(-1000, -1000);

    // Limpa bolas extras
    for(DuBallItem* ball : mBallList) {
        removeItem(ball);
        delete ball;
    }
    mBallList.clear();

    // Limpa blocos extras
     for(QGraphicsItem* block : mBlockList) {
         removeItem(block);
         delete block;
    }
    mBlockList.clear();

    // Recria blocos iniciais
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {

            int x = 50 + (i * 80);
            int y = 50 + (j * 40);
            int vida = 3 - j;

            duBlockItem* newBlock = new duBlockItem(vida, x, y, 70, 30, Qt::green);
            addItem(newBlock);
            mBlockList.append(newBlock);
        }
        for (int j = 0; j < 2; ++j) {

            int x = 50 + (i * 80);
            int y = 50 + (j * 40);
            int vida = 3 - j;

            duBlockItem* newBlock = new duBlockItem(vida, x, y+120, 70, 30, Qt::green);
            addItem(newBlock);
            mBlockList.append(newBlock);
        }
    }

    /*
    QGraphicsRectItem* block2 = addRect(350, 100, 150, 50, QPen(Qt::black), QBrush(Qt::white));
    mWallList.append(block2);
    */

    mCurrentPhase = 0;
    mCompletedPhases = 0;
    generateRandomPhaseOrder();


    for(DuBallItem* ball : mBallList) {
        removeItem(ball);
        delete ball;
    }
    mBallList.clear();

    //recria bola inicial verde
    DuBallItem* newBall = new DuBallItem((XPLATFORM+35), (YPLATFORM-20), WBALL, HBALL, VXBALL, -VYBALL, 0.0f, Qt::green);
    addItem(newBall);
    mBallList.append(newBall);

    int firstPhase = mPhaseOrder[0];
    createBlocksForPhase(firstPhase);

    mPlatformItem->setx(XPLATFORM);
    mPlatformItem->sety(YPLATFORM);
    mPlatformItem->setvx(VXPLATFORM);
    mPlatformItem->setPos(XPLATFORM, YPLATFORM);
    mPlatformItem->resetPlatformSize();
    //mPlatformItem->mCurrentVx(0);

    update();
    emit gameReset();
}

void DuGraphicsScene::stopScene()
{
    mThreadTimer->terminate();
}

void DuGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    mPlatformItem->keyPress(event->key());
    if (event->key() == Qt::Key_Space) {
        if (mBallList.isEmpty()) {
            resetScene();
            mThreadTimer->start();
        }
        /*if (mBallList.size() >> 0) {
            mThreadTimer->start();
        }*/
        if (mBallList.size() >> 0 && mBlockList.isEmpty()){
            resetScene();
            mThreadTimer->start();
        }
    }
    if(event->key() == Qt::Key_Escape){
        emit gameQuit();
    }
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
    //xrandomNumber = QRandomGenerator::global()->bounded(xmin, xmax);
    DuBallItem* firstBall = new DuBallItem((XPLATFORM+35), (YPLATFORM-20), WBALL, HBALL, VXBALL, -VYBALL, 0.0f, Qt::green);
    mBallList.append(firstBall);
    mPlatformItem = new DuPlatformItem(XPLATFORM, YPLATFORM, WPLATFORM, HPLATFORM, VXPLATFORM, VYPLATFORM);
    xrandomNumber = QRandomGenerator::global()->bounded(xmin, xmax);
     mPowerUpItem = new DuPowerUpItem(xrandomNumber, YPWRUP, WPWRUP, HPWRUP, VXPWRUP, VYPWRUP, POWERUP_MULTIBALL);

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
    mPowerUpItem->hide();
    // ordem aleatoria das fases
    generateRandomPhaseOrder();
    int firstPhase = mPhaseOrder[0];
    createBlocksForPhase(firstPhase);
    // QGraphicsRectItem* wall = addRect(0, 100, 150, 50, QPen(Qt::black), QBrush(Qt::white));
    // mWallList.append(wall);

    // QGraphicsRectItem* wall2 = addRect(350, 100, 150, 50, QPen(Qt::black), QBrush(Qt::white));
    // mWallList.append(wall2);

    // duBlockItem* block : mBlockList;

}
void DuGraphicsScene::connectObjects()
{
    connect(mThreadTimer, &DuThreadTimer :: timeOut, this, &DuGraphicsScene :: updateScene);
}

void DuGraphicsScene::updateScene()
{
    mPlatformItem->move();
    //mPowerUpItem->move();

    if (mPowerUpItem->isVisible()) {
        mPowerUpItem->move();

        if (mPowerUpItem->gety() > YSIZE) {
            mPowerUpItem->hide();
        }
    }

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

                    /* Aceleração linear */
                    if(QRandomGenerator::global()->bounded(0, 100) < 40){
                        int bvx = ball->getvx();
                        int bvy = ball->getvy();

                        // Acelera X
                        if(DuUtil::abs(bvx) < MAX_SPEED){
                            if (bvx > 0) bvx++; else bvx--;
                        }

                        // Acelera Y
                        if(DuUtil::abs(bvy) < MAX_SPEED){
                            if (bvy > 0) bvy++; else bvy--;
                        }
                        ball->setvx(bvx);
                        ball->setvy(bvy);
                    }

                    removeItem(block);
                    mBlockList.removeAt(j);
                    mTotalScore += 1000;
                    delete block;

                    /* Spawn do PowerUp */

                    if (!mPowerUpItem->isVisible()) {
                        if (QRandomGenerator::global()->bounded(0, 100) < 90) {

                            PowerUpType randomType;
                            if (QRandomGenerator::global()->bounded(0, 100) < 50) {
                                randomType = POWERUP_MULTIBALL;
                            } else {
                                randomType = POWERUP_EXPAND_PLATFORM;
                            }

                            int blockX = block->getx();
                            int blockY = block->gety();
                            int blockW = block->getw();

                            int pwrX = blockX + (blockW / 2) - (mPowerUpItem->getw() / 2);
                            int pwrY = blockY;

                            removeItem(mPowerUpItem);
                            delete mPowerUpItem;
                            mPowerUpItem = new DuPowerUpItem(pwrX, pwrY, WPWRUP, HPWRUP, 0, VYPWRUP, randomType);
                            addItem(mPowerUpItem);
                            mPowerUpItem->setPos(pwrX, pwrY);
                            mPowerUpItem->show();
                        }
                    }
                }
                else {
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

        if(ball->collidesWithItem(mPlatformItem)){
            checkCollisions(ball);
        }     

        if (ball->gety() >= (YSIZE - (HBALL-50))) {
            removeItem(ball);
            mBallList.removeAt(i);
            delete ball;
            i--;
        }
    }

    // Checa GAME WIN

    if(mBlockList.isEmpty()){
        mCompletedPhases++;

        if (mCompletedPhases >= 3) {
            stopScene();
            emit gameWin();
            return;
        }
        else {
            mCurrentPhase++;
            loadNextPhase();
            return;

        }
    }

    if (mBallList.isEmpty()) {
        stopScene();
        emit gameLose();
        return;
    }
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

void DuGraphicsScene::generateRandomPhaseOrder()
{
    mPhaseOrder.clear();
    mPhaseOrder.append(0);
    mPhaseOrder.append(1);
    mPhaseOrder.append(2);

    for (int i = mPhaseOrder.size() - 1; i > 0; --i) {
        int j = QRandomGenerator::global()->bounded(0, i + 1);
        mPhaseOrder.swapItemsAt(i, j);
    }
}

void DuGraphicsScene::createBlocksForPhase(int phaseIndex)
{
    // Limpa blocos existentes
    for(QGraphicsItem* block : mBlockList) {
        removeItem(block);
        delete block;
    }
    mBlockList.clear();

    switch(phaseIndex) {
    case 0: // Fase 1
    {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 3; ++j) {
                int x = 50 + (i * 80);
                int y = 50 + (j * 40);
                int vida = 3 - j;

                duBlockItem* newBlock = new duBlockItem(vida, x, y, 70, 30, Qt::green);
                addItem(newBlock);
                mBlockList.append(newBlock);
            }
            for (int j = 0; j < 2; ++j) {
                int x = 50 + (i * 80);
                int y = 50 + (j * 40);
                int vida = 3 - j;

                duBlockItem* newBlock = new duBlockItem(vida, x, y+120, 70, 30, Qt::green);
                addItem(newBlock);
                mBlockList.append(newBlock);
            }
        }
        break;
    }

    case 1: // Fase 2
    {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 5; ++j) {
                // Cria padrão xadrez
                if ((i + j) % 2 == 0) {
                    int x = 30 + (i * 75);
                    int y = 50 + (j * 35);
                    int vida = (j % 3) + 1;

                    duBlockItem* newBlock = new duBlockItem(vida, x, y, 65, 25, Qt::green);
                    addItem(newBlock);
                    mBlockList.append(newBlock);
                }
            }
        }
        break;
    }

    case 2: // Fase 3
    {
        // 5 blocos
        for (int i = 0; i < 5; ++i) {
            int x = 75 + (i * 70);
            int y = 50;
            duBlockItem* newBlock = new duBlockItem(3, x, y, 60, 30, Qt::green);
            addItem(newBlock);
            mBlockList.append(newBlock);
        }

        // 4 blocos
        for (int i = 0; i < 4; ++i) {
            int x = 110 + (i * 70);
            int y = 90;
            duBlockItem* newBlock = new duBlockItem(2, x, y, 60, 30, Qt::green);
            addItem(newBlock);
            mBlockList.append(newBlock);
        }

        // 3 blocos
        for (int i = 0; i < 3; ++i) {
            int x = 145 + (i * 70);
            int y = 130;
            duBlockItem* newBlock = new duBlockItem(2, x, y, 60, 30, Qt::green);
            addItem(newBlock);
            mBlockList.append(newBlock);
        }

        // 2 blocos
        for (int i = 0; i < 2; ++i) {
            int x = 180 + (i * 70);
            int y = 170;
            duBlockItem* newBlock = new duBlockItem(1, x, y, 60, 30, Qt::green);
            addItem(newBlock);
            mBlockList.append(newBlock);
        }

        //1 bloco
        duBlockItem* newBlock = new duBlockItem(1, 215, 210, 60, 30, Qt::green);
        addItem(newBlock);
        mBlockList.append(newBlock);

        break;
    }
    }
}

void DuGraphicsScene::loadNextPhase()
{

    for(int i = mBallList.size() - 1; i > 0; --i) {
        DuBallItem* ball = mBallList[i];
        removeItem(ball);
        mBallList.removeAt(i);
        delete ball;
    }

    if (!mBallList.isEmpty()) {
        DuBallItem* mainBall = mBallList.first();
        mainBall->setx(XPLATFORM + 35);
        mainBall->sety(YPLATFORM - 20);
        mainBall->setvx(VXBALL);
        mainBall->setvy(-VYBALL);
        mainBall->setPos(XPLATFORM + 35, YPLATFORM - 20);
    }

    mPowerUpItem->hide();
    mPowerUpItem->setPos(-1000, -1000);

    mPlatformItem->setx(XPLATFORM);
    mPlatformItem->sety(YPLATFORM);
    mPlatformItem->setvx(VXPLATFORM);
    mPlatformItem->setPos(XPLATFORM, YPLATFORM);

    int phaseToLoad = mPhaseOrder[mCurrentPhase];
    createBlocksForPhase(phaseToLoad);

    update();
}


void DuGraphicsScene::collectedPwrUp()
{
    PowerUpType type = mPowerUpItem->getType();

    mPowerUpItem->hide();
    mPowerUpItem->setPos(-1000, -1000);

    mPlatformItem->resetPlatformSize();
    //powerups
    if (type == POWERUP_MULTIBALL) {
        DuBallItem* newBall = new DuBallItem(XPLATFORM, (YPLATFORM-10), WBALL, HBALL, VXBALL, -VYBALL, 0.0f, Qt::yellow);
        addItem(newBall);
        mBallList.append(newBall);

        DuBallItem* newBall2 = new DuBallItem((XPLATFORM-20), (YPLATFORM-30), WBALL, HBALL, -VXBALL, -VYBALL, 0.0f, Qt::yellow);
        addItem(newBall2);
        mBallList.append(newBall2);
    }
    else if (type == POWERUP_EXPAND_PLATFORM) {
        mPlatformItem->expandPlatform();
    }
}

