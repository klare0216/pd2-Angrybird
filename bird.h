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
    ~Bird();
    void setLinearVelocity(b2Vec2 velocity);
    void setLinearVelocity(int qt_x, int qt_y);
    void setPos(float qt_x, float qt_y);
    virtual void useSkill();
    virtual int type();
    static bool stop;
    void setIsDone(bool value);

public slots:
    void done();

protected:
    bool is_skill_used;
    int done_count;
    bool isDone;
};

#endif // BIRD_H
