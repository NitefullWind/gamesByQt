#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

#include "controller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene(-300,-400,600,800,this);
    view = new QGraphicsView(scene,this);
    controller = new Controller(*scene,this);
    ui->setupUi(this);
    setCentralWidget(view);
    setFixedSize(630,840);
}

MainWindow::~MainWindow()
{
    delete ui;
}
