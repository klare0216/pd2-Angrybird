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
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QList<GameItem *> birdList;
    QTimer timer;
    abContactListener *contactListener;

    // For MouseEvent
    bool hasBird;
    bool isStart;
    int bullet_num;
};

#endif // MAINWINDOW_H
