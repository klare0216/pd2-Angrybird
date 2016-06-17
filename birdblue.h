#ifndef BIRDBLUE_H
#define BIRDBLUE_H
#include <bird.h>

class BirdBlue : public Bird
{
public:
   BirdBlue(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
  // virtual void useSkill();
};

#endif // BIRDBLUE_H
