#include "duthreadtimer.h"

DuThreadTimer::DuThreadTimer(int miliseconds, QObject *parent) : QThread(parent)
{
    mMiliseconds = miliseconds;
}

void DuThreadTimer::run()
{
    while(true){
        emit timeOut();
        QThread::msleep(mMiliseconds);
    }
}
