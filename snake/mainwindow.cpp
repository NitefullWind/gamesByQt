#include <QGraphicsView>

#include "constants.h"
#include "controller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene(-450,-300,SceneWidth+100,SceneHeight,this);
    view = new QGraphicsView(scene,this);
    controller = new Controller(*scene,this);
    ui->setupUi(this);
    setCentralWidget(view);
    setFixedSize(950,650);
    setWindowTitle(tr("两条小蛇"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
