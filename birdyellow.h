#ifndef BIRDYELLOW_H
#define BIRDYELLOW_H
#include <bird.h>

class BirdYellow : public Bird
{
public:
   BirdYellow(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene);
   virtual void useSkill();


};

#endif // BIRDYELLOW_H
