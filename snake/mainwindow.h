#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class Controller;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Controller *controller;
    QGraphicsScene *scene;
    QGraphicsView *view;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW

