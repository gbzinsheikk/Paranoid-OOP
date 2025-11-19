#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "duarkanoid.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mArkanoid = new DuArkanoid(ui->graphicsView, this);
    //setCentralWidget(ui->graphicsView);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::iniciarJogo);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::encerrarJogo);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniciarJogo()
{
    mArkanoid->startGame();
}

void MainWindow::encerrarJogo()
{
    mArkanoid->stopGame();
    close();
}
