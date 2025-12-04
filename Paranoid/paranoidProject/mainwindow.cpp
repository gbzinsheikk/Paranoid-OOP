#include "mainwindow.h"
#include "dugraphicsscene.h"
#include "DuGlobalDefines.h"

#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QProgressBar>
#include <QKeyEvent>
//#include <QVBoxLayout>

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

    QLabel *speedLabel = new QLabel("Main Ball\n  Speed", this);
    speedLabel->setFont(font);
    speedLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    speedLabel->setStyleSheet("QLabel { background-color: #00FF00; }"); // Base: #00FF00 (Verde)

    mSpeedBar = new QProgressBar(this);
    mSpeedBar->setRange(0, MAX_SPEED);
    mSpeedBar->setValue(0);
    mSpeedBar->setTextVisible(true);
    mSpeedBar->setFormat("%v");

    mSpeedBar->setStyleSheet("QProgressBar::chunk { background-color: #00FF00; }"); // Base: #00FF00 (Verde)

    mScoreDisplay = new QLCDNumber(this);
    QPalette paletteScoreDisplay = mScoreDisplay->palette();
    paletteScoreDisplay.setColor(QPalette::WindowText, Qt::red);
    paletteScoreDisplay.setColor(QPalette::Light, QColor(255, 100, 100));
    paletteScoreDisplay.setColor(QPalette::Dark, QColor(255, 100, 100));

    mScoreDisplay->setPalette(paletteScoreDisplay);
    mScoreDisplay->display(0);

    scoretext->setPalette(paletteScoreDisplay);

    mView = new QGraphicsView(this);
    mScene = new DuGraphicsScene(this);
    mView->setScene(mScene);

    mBotaoIniciar->setFixedSize(70, 40);
    mBotaoReset->setFixedSize(70, 40);
    mBotaoQuitar->setFixedSize(70, 40);

    mWinLabel = new QLabel("YOU WIN!", this);
    mWinLabel->setGeometry(125, 200, 300, 60);
    mWinLabel->setAlignment(Qt::AlignCenter);
    QFont winFont = mWinLabel->font();
    winFont.setPointSize(30);
    winFont.setBold(true);
    mWinLabel->setFont(winFont);
    mWinLabel->setStyleSheet("QLabel { color : green; background-color: white; border: 2px solid black; }");
    mWinLabel->hide();

    mFinalScore = new QLCDNumber(this);
    mFinalScore->setGeometry(175, 270, 200, 80);
    mFinalScore->setPalette(paletteScoreDisplay);
    mFinalScore->setDigitCount(5);
    mFinalScore->hide();

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(mBotaoIniciar);
    buttonsLayout->addWidget(mBotaoReset);
    buttonsLayout->addWidget(mBotaoQuitar);

    buttonsLayout->addStretch();

    buttonsLayout->addSpacing(20);
    buttonsLayout->addWidget(speedLabel);
    buttonsLayout->addWidget(mSpeedBar);

    buttonsLayout->addWidget(scoretext);
    buttonsLayout->addWidget(mScoreDisplay);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(mView);

    connect(mScene, &DuGraphicsScene::speedChanged, this, &MainWindow::updateSpeed);
    connect(mScene, &DuGraphicsScene::scoreChanged, this, &MainWindow::updateScore);
    connect(mBotaoIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJogo);
    connect(mBotaoReset, &QPushButton::clicked, this, &MainWindow::resetarJogo);
    connect(mBotaoQuitar, &QPushButton::clicked, this, &MainWindow::encerrarJogo);
    connect(mScene, &DuGraphicsScene::gameOver, this, &MainWindow::resetButtonOn);
    connect(mScene, &DuGraphicsScene::gameReset, this, &MainWindow::atualizarBotoes);
    connect(mScene, &DuGraphicsScene::gameWin, this, &MainWindow::ganhouJogo);
    connect(mScene, &DuGraphicsScene::gameQuit, this, &MainWindow::encerrarJogo);

    mBotaoReset->setEnabled(false);
}

MainWindow::~MainWindow()
{

}

void MainWindow::iniciarJogo()
{
    //mArkanoid->startGame();
    mScene->startScene();
    mView->setFocus();
    mBotaoReset->setEnabled(false);
    mBotaoIniciar->setEnabled(false);

    mWinLabel->hide();
    mFinalScore->hide();
}

void MainWindow::resetarJogo()
{
    //mArkanoid->resetGame();
    mScene->resetScene();
    //mScoreDisplay->display(0);
    mView->setFocus();
    mBotaoIniciar->setEnabled(true);
    mBotaoReset->setEnabled(false);

    mWinLabel->hide();
    mFinalScore->hide();
}

void MainWindow::resetButtonOn()
{
    mBotaoReset->setEnabled(true);
}

void MainWindow::encerrarJogo()
{
    //mArkanoid->stopGame();
    mScene->stopScene();
    close();
}

void MainWindow::updateScore(int score)
{
    mScoreDisplay->display(score);
}

void MainWindow::updateSpeed(int speed)
{
    mSpeedBar->setValue(speed);
}

void MainWindow::atualizarBotoes()
{
    mBotaoIniciar->setEnabled(false);
    mBotaoReset->setEnabled(false);

    mWinLabel->hide();
    mFinalScore->hide();
    mView->setFocus();
}

void MainWindow::ganhouJogo()
{
    mBotaoIniciar->setEnabled(false);
    mBotaoReset->setEnabled(true);

    mFinalScore->display(mScoreDisplay->intValue());
    mWinLabel->raise();
    mFinalScore->raise();
    mWinLabel->show();
    mFinalScore->show();
    mView->setFocus();
}
