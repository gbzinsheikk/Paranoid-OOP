#include "mainwindow.h"
#include "duarkanoid.h"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->resize(1000, 700);
    this->setFixedSize(550, 700);
    this->setWindowTitle("Paranoid");

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    mBotaoIniciar = new QPushButton("PLAY", this);
    mBotaoReset = new QPushButton("RESET", this);
    mBotaoQuitar = new QPushButton("QUIT", this);
    mView = new QGraphicsView(this);

    mBotaoIniciar->setFixedSize(100, 40);
    mBotaoReset->setFixedSize(100, 40);
    mBotaoQuitar->setFixedSize(100, 40);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(mBotaoIniciar);
    buttonsLayout->addWidget(mBotaoReset);
    buttonsLayout->addWidget(mBotaoQuitar);
    buttonsLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(mView);

    mArkanoid = new DuArkanoid(mView, this);

    connect(mBotaoIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJogo);
    connect(mBotaoReset, &QPushButton::clicked, this, &MainWindow::resetarJogo);
    connect(mBotaoQuitar, &QPushButton::clicked, this, &MainWindow::encerrarJogo);
}

MainWindow::~MainWindow()
{

}

void MainWindow::iniciarJogo()
{
    mArkanoid->startGame();
    mView->setFocus();
}

void MainWindow::resetarJogo()
{
    mArkanoid->resetGame();
    mView->setFocus();
}

void MainWindow::encerrarJogo()
{
    mArkanoid->stopGame();
    close();
}

