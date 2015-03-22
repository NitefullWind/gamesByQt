#ifndef MAINWINDOW
#define MAINWINDOW
#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class Controller;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Controller *game;
    QLabel *scoreLabel;
private slots:
    void showScore(const int &score);
    void hideScore(const bool is);
};

#endif // MAINWINDOW

