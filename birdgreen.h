#ifndef BIRDGREEN_H
#define BIRDGREEN_H
#include <bird.h>

class BirdGreen: public Bird
{
public:
   BirdGreen(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
   virtual void useSkill();
   virtual int type();
};

#endif // BIRDGREEN_H
