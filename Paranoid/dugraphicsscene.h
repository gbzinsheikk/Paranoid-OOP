#ifndef DUGRAPHICSSCENE_H
#define DUGRAPHICSSCENE_H

#include <QGraphicsScene>

class DuThreadTimer;

class DuGraphicsScene : public QGraphicsScene
{
public:
    DuGraphicsScene(Object *parent = nullptr);
    void startScene();
    void stopScene();
private:
    DuThreadTimer *mThreadTimer;
};

#endif // DUGRAPHICSSCENE_H
