#ifndef ENEMY_H
#define ENEMY_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#include <iostream>


#define ENEMY_DENSITY 10.0f
#define ENEMY_FRICTION 0.2f
#define ENEMY_RESTITUTION 0.5f

class Enemy : public GameItem
{
public:
    Enemy(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
    ~Enemy();
    virtual void StartContact(GameItem*body);
    virtual int type();
    static int *e_score;
    static int add_score;
    static  QList<GameItem *> *list_ptr;
protected:

};

#endif // ENEMY_H
