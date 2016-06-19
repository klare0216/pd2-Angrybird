#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <typeinfo>
#include <exception>

#include <gameitem.h>
#include <land.h>
#include <birdyellow.h>
#include <birdblue.h>
#include <birdblack.h>
#include <birdgreen.h>
#include <birdwhite.h>
#include <enemy.h>
#include <barrier.h>
#include <abcontactlistener.h>
#include <background.h>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    static int const EXIT_CODE_REBOOT = -878787;

signals:
    // Signal for closing the game
    void quitGame();
    void Restart();
    void gameOver();
    void win();


private slots:
    void tick();
    void restart();
    void GAMEOVER();
    void WIN();
    // For debug slot
    void QUITSLOT();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QList<GameItem *> birdList;
    QList<GameItem *> EnemyList;
    QTimer timer;
    abContactListener *contactListener;
    BackGround *background;
    int score;

    // For MouseEvent
    Bird * focus_bird;
    bool hasBird;
    bool isStart;
    int bullet_num;


};

#endif // MAINWINDOW_H
