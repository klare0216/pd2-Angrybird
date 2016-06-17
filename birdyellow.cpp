#include "birdyellow.h"

BirdYellow::BirdYellow(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene) :
    Bird(qt_x, qt_y, qt_radius, timer, image_path, world, scene)
{

}

void BirdYellow::useSkill()
{
    std::cout << "use yellow bird's skill!" << std::endl;
}
