#include "mainwindow.h"
#include "duarkanoid.h"
#include "dugraphicsscene.h"
//#include "duballitem.h"
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>

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

    QLabel *scoretext = new QLabel(this);
    scoretext->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    scoretext->setText("Score");
    QFont font = scoretext->font();
    font.setBold(true);
    scoretext->setFont(font);
    //scoretext->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    mScoreDisplay = new QLCDNumber(this);
    //mScoreDisplay->setSegmentStyle(QLCDNumber::Flat);
    QPalette paletteScoreDisplay = mScoreDisplay->palette();
    paletteScoreDisplay.setColor(QPalette::WindowText, Qt::red);
    paletteScoreDisplay.setColor(QPalette::Light, QColor(255, 100, 100));
    paletteScoreDisplay.setColor(QPalette::Dark, QColor(255, 100, 100));
    mScoreDisplay->setPalette(paletteScoreDisplay);
    mScoreDisplay->display(0);

    scoretext->setPalette(paletteScoreDisplay);

    mView = new QGraphicsView(this);

    mBotaoIniciar->setFixedSize(100, 40);
    mBotaoReset->setFixedSize(100, 40);
    mBotaoQuitar->setFixedSize(100, 40);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(mBotaoIniciar);
    buttonsLayout->addWidget(mBotaoReset);
    buttonsLayout->addWidget(mBotaoQuitar);

    buttonsLayout->addStretch();

    buttonsLayout->addWidget(scoretext);
    buttonsLayout->addWidget(mScoreDisplay);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(mView);

    mArkanoid = new DuArkanoid(mView, this);

    connect(mArkanoid->getScene(), &DuGraphicsScene::scoreChanged, this, &MainWindow::updateScore);
    connect(mBotaoIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJogo);
    connect(mBotaoReset, &QPushButton::clicked, this, &MainWindow::resetarJogo);
    connect(mBotaoQuitar, &QPushButton::clicked, this, &MainWindow::encerrarJogo);

    connect(mArkanoid->getScene(), &DuGraphicsScene::gameOver, this, &MainWindow::resetButtonOn);
    mBotaoReset->setEnabled(false);
}

MainWindow::~MainWindow()
{

}

void MainWindow::iniciarJogo()
{
    mArkanoid->startGame();
    mView->setFocus();
    mBotaoReset->setEnabled(false);
    mBotaoIniciar->setEnabled(false);
}

void MainWindow::resetarJogo()
{
    mArkanoid->resetGame();
    //mScoreDisplay->display(0);
    mView->setFocus();
    mBotaoIniciar->setEnabled(true);
    mBotaoReset->setEnabled(false);
}

void MainWindow::resetButtonOn()
{
    mBotaoReset->setEnabled(true);
}

void MainWindow::encerrarJogo()
{
    mArkanoid->stopGame();
    close();
}

void MainWindow::updateScore(int score)
{
    mScoreDisplay->display(score);
}
