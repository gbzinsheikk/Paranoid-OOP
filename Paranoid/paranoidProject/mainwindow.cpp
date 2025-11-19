#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "duarkanoid.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mArkanoid = new DuArkanoid(ui->graphicsView, this);
    setCentralWidget(ui->graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionIniciar_triggered()
{
    mArkanoid->startGame();
}


void MainWindow::on_actionQuitar_triggered()
{
    mArkanoid->stopGame();
    close();
}

