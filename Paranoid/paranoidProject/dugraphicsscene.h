#ifndef DUGRAPHICSSCENE_H
#define DUGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QList>

class DuThreadTimer;
class DuBallItem;
class DuPlatformItem;
class DuPowerUpItem;

class DuGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DuGraphicsScene(QObject *parent = nullptr);
    void startScene();
    void resetScene();
    void stopScene();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void createObjects();
    void configureObjects();
    void connectObjects();
    void updateScene();
    //void checkCollisions();
    void checkCollisions(DuBallItem* ball);
    void collectedPwrUp();

    DuThreadTimer *mThreadTimer;
    //DuBallItem *mBallItem;
    QList<DuBallItem*> mBallList;
    DuPlatformItem *mPlatformItem;
    DuPowerUpItem *mPowerUpItem;

    int mTotalScore;

signals:
    void scoreChanged(int newScore);
    void speedChanged(int newSpeed);
    void gameOver();  
};

#endif // DUGRAPHICSSCENE_H
