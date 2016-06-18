#ifndef EGG_H
#define EGG_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#include <string>
#include <iostream>

#define EGG_DENSITY 5.0f
#define EGG_FRICTION 0.2f
#define EGG_RESTITUTION 0.5f

class Egg : public GameItem
{
public:
    Egg(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path,  b2World *world, QGraphicsScene *scene);
    virtual int type();
};

#endif // EGG_H
