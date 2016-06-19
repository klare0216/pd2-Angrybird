#include "birdgreen.h"

BirdGreen::BirdGreen(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene) :
    Bird(qt_x, qt_y, qt_radius, timer, image_path, world, scene)
{
}

void BirdGreen::useSkill()
{
    std::cout << "use green bird's skill!" << std::endl;
    if (!is_skill_used)
    {
        b2Vec2 velocity(g_body->GetLinearVelocity().x * (0), -20);
        setLinearVelocity(velocity);
        is_skill_used = true;
    }
}

int BirdGreen::type()
{
    return type_birdgreen;
}
