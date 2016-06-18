#include "birdblack.h"

BirdBlack::BirdBlack(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene) :
    Bird(qt_x, qt_y, qt_radius, timer, image_path, world, scene)
{

}

void BirdBlack::useSkill()
{
    std::cout << "use black bird's skill!" << std::endl;
    if (!is_skill_used)
    {
         // update g_size g_body g_pixmap
        float b_radius = g_size.x * 2;
            //update g_size
        g_size.Set(b_radius * 2, b_radius * 2);
            // update g_body
        b2CircleShape bodyshape;
        bodyshape.m_radius = b_radius;
        b2FixtureDef fixturedef;
        fixturedef.shape = &bodyshape;
        fixturedef.density = BIRD_DENSITY;
        fixturedef.friction = BIRD_FRICTION;
        fixturedef.restitution = BIRD_RESTITUTION;
        g_body->DestroyFixture(g_body->GetFixtureList());
        g_body->CreateFixture(&fixturedef);
            //update g_pixmap
        int qt_radius = QtX(b_radius);
        QPixmap pixmap = g_pixmap.pixmap().scaled(qt_radius * 2, qt_radius * 2);
        g_pixmap.setPixmap(pixmap);
        g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);

        is_skill_used = true;
    }
}

int BirdBlack::type()
{
    return type_birdblack;
}
