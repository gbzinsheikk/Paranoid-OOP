#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlcdnumber.h"
#include "dugraphicsscene.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QTimer>
//#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateScore(int score);
    void updateSpeed(int speed);

private slots:
    void iniciarJogo();
    void encerrarJogo();
    void resetarJogo();
    void resetButtonOn();

private:
    QPushButton *mBotaoIniciar;
    QPushButton *mBotaoReset;
    QPushButton *mBotaoQuitar;
    QLCDNumber *mScoreDisplay;
    QGraphicsView *mView;
    DuGraphicsScene *mScene;
    QProgressBar *mSpeedBar;

protected:

};
#endif // MAINWINDOW_H
