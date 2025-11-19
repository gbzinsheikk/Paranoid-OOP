#include "duthreadtimer.h"

DuThreadTime::DuThreadTimer(int miliseconds, QObject *parent) : QThread(parent)
{
    mMiliseconds = miliseconds;
}

void DuThreadTime::run()
{
    while(true){
        emit timeOut();
        QThread::msleep(mMiliseconds);
    }
}
