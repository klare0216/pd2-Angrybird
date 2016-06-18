#ifndef BARRIER_H
#define BARRIER_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#include <iostream>


#define BERRIER_DENSITY 87.0f
#define  BERRIER_FRICTION 0.2f
#define  BERRIER_RESTITUTION 0.5f

class Barrier : public GameItem
{
public:
    Barrier (int qt_x,  int qt_y, int qt_w, int qt_h, float angle, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
    virtual int type();
    virtual void StartContact(GameItem *contact_body);
};

#endif // BARRIER_H
