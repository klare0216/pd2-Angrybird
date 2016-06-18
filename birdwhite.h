#ifndef BIRDWHITE_H
#define BIRDWHITE_H
#include <bird.h>
#include <egg.h>

class BirdWhite : public Bird
{
public:
   BirdWhite(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
   virtual void useSkill();
   virtual int type();
protected:
   int eggs_index;
};
#endif // BIRDWHITE_H
