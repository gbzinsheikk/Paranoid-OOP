#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "duarkanoid.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "duarkanoid.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class DuArkanoid;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void encerrarJogo();

private slots:
    void iniciarJogo();
    void encerrarJogo();
    void resetarJogo();
    //void on_pushButton_clicked();

private:
    QPushButton *mBotaoIniciar;
    QPushButton *mBotaoReset;
    QPushButton *mBotaoQuitar;
    QGraphicsView *mView;

    DuArkanoid *mArkanoid;
};
#endif // MAINWINDOW_H
