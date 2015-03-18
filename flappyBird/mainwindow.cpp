#include <QGraphicsView>
#include <QTimer>
#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "controller.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,scoreLabel(new QLabel(this))
{
    newGame();
    scoreLabel->setFixedSize(150,50);
    scoreLabel->setStyleSheet("background:rgba(0,0,0,0,0)");

    setFixedSize(402,602);
}


void MainWindow::showScore(const int &score)
{
    scoreLabel->setText(tr("<h1>Score: %1</h1>").arg(score));
}

void MainWindow::gameOver()
{
    QWidget *widget = new QWidget;
    QPushButton *newGameButton = new QPushButton(tr("PLAY ANAIN"));
    connect(newGameButton,SIGNAL(clicked()),this,SLOT(newGame()));
    QVBoxLayout vLayout;
    vLayout.addStretch();
    vLayout.addWidget(scoreLabel);
    vLayout.addWidget(newGameButton);
    vLayout.addStretch();
    widget->setLayout(&vLayout);
    setCentralWidget(widget);
}

void MainWindow::newGame()
{
    scene = new QGraphicsScene(0,0,400,600,this);
    view = new QGraphicsView(scene,this);
    game = new Controller(*scene,this);

    view->setBackgroundBrush(QPixmap(":/files/bg.jpg"));
    scene->addWidget(scoreLabel);
    showScore(0);

    connect(game,SIGNAL(scoreChanged(int)), this, SLOT(showScore(int)));
    connect(game,SIGNAL(gameIsOver()),this,SLOT(gameOver()));
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{

}
