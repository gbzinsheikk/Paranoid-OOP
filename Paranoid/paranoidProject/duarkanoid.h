#ifndef DUARKANOID_H
#define DUARKANOID_H

#include <QObject>
#include <QWidget>

class DuGraphicsScene;
//class DuGraphicsView;
class QGraphicsView;

class DuArkanoid : public QObject
{
public:
    DuArkanoid(QGraphicsView *graphicsView, QObject *parent = nullptr);
    void startGame();
    void resetGame();
    void stopGame();
private:
    DuGraphicsScene *mScene;
};

#endif // DUARKANOID_H
