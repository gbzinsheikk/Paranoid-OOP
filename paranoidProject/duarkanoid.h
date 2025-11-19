#ifndef DUARKANOID_H
#define DUARKANOID_H

#include <QObject>

class DuGraphicsScene;
class DuGraphicsView;

class DuArkanoid : public QObject
{
public:
    DuArkanoid(QGraphicsView *graphicsView, QObject *parent = nullptr);
    void startGame();
    void stopGame();
private:
    DuGraphicsScene *mScene;
};

#endif // DUARKANOID_H
