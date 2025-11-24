#ifndef DUGRAPHICSSCENE_H
#define DUGRAPHICSSCENE_H

#include <QGraphicsScene>

class DuThreadTimer;
class DuBallItem;
class DuPlatformItem;

class DuGraphicsScene : public QGraphicsScene
{
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
    void checkCollisions();

    DuThreadTimer *mThreadTimer;
    DuBallItem *mBallItem;
    DuPlatformItem *mPlatformItem;
};

#endif // DUGRAPHICSSCENE_H
