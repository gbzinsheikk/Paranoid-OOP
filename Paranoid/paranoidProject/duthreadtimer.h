#ifndef DUTHREADTIMER_H
#define DUTHREADTIMER_H

#include <QThread>

class DuThreadTimer : public QThread
{
        Q_OBJECT
public:
    DuThreadTimer(int miliseconds, QObject *parent = nullptr);
signals:
    void timeOut();
protected:
    void run() override;
private:
    int mMiliseconds;
};

#endif // DUTHREADTIMER_H
