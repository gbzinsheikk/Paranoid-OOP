#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_actionIniciar_triggered();
    void on_actionQuitar_triggered();

private:
    Ui::MainWindow *ui;
    DuArkanoid *mArkanoid;
};
#endif // MAINWINDOW_H
