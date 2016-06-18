#ifndef BIRDBLACK_H
#define BIRDBLACK_H
#include <bird.h>

class BirdBlack : public Bird
{
public:
   BirdBlack(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
   virtual void useSkill();
   virtual int type();
};

#endif // BIRDBLACK_H
