#ifndef BIRD_H
#define BIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#include <string>
#include <iostream>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Bird : public GameItem
{
public:
    Bird(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void setLinearVelocity(int qt_x, int qt_y);
    void setPos(float x, float y);
    virtual void useSkill();
protected:
    bool is_skill_used;
};

#endif // BIRD_H
