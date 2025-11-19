#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "duarkanoid.h"

#include <QMainWindow>

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

private slots:
    void iniciarJogo();
    void encerrarJogo();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DuArkanoid *mArkanoid;
};
#endif // MAINWINDOW_H
