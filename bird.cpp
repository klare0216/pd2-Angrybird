#include "bird.h"

Bird::Bird(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path,  b2World *world, QGraphicsScene *scene):GameItem(world)
{

    // Change unit fom qt to box2d
        // length
    float b_radius = qt_radius / g_windowsize.width() * g_worldsize.width();
        // Set g_size
    g_size.Set(b_radius * 2, b_radius * 2);
        // pos
    float b_x =  qt_x * g_worldsize.width() / g_windowsize.width();
    float b_y = (1.0f - qt_y / g_windowsize.height())* g_worldsize.height() ;


    // Set pixmap
    g_pixmap.setPixmap(QPixmap(image_path).scaled(qt_radius * 2, qt_radius * 2));
    g_pixmap.setTransformationMode(Qt::SmoothTransformation);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);


    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(b_x, b_y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = b_radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetSleepingAllowed(true);


    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Bird::setLinearVelocity(int qt_x, int qt_y)
{

    // give the range to set the pos x
     if (qt_x > 200)
        qt_x = 200;
     else if (qt_x < 100)
        qt_x =100;
    // give the range to set the pos y
     if (qt_y > 380)
        qt_y = 380;
    else if (qt_y < 300)
        qt_y =300;
     // change qt pos to box2d pos
    float x = (200 - qt_x)* g_worldsize.width() / g_windowsize.width() + g_size.x/2.0f;
    float y = (1.0f - qt_y / g_windowsize.height())* g_worldsize.height() - g_size.y/2.0f;
    y =  ((1.0f - 300 / g_windowsize.height())* g_worldsize.height() - g_size.y/2.0f ) - y;
    //std::cout << " (x , y) = (" <<  x <<","<< y << ")" << std::endl;
    // set linear velocity
    b2Vec2 velocity(x * 4, y * 4);
    g_body->SetLinearVelocity(velocity);
}

void Bird::setPos(float x, float y)
{
    b2Vec2 pos;
    // give the range to set the pos x
     if (x > 200)
        x = 200;
     else if (x < 100)
        x =100;
    // give the range to set the pos y
     if (y > 380)
        y = 380;
    else if (y < 300)
        y =300;
   // change the qt pos to box2d pos
   pos.x =  x * g_worldsize.width() / g_windowsize.width();
   pos.y = (1.0f - y / g_windowsize.height())* g_worldsize.height();
    // set g_body's pos, and not to change the rotation
   g_body->SetTransform(pos,g_body->GetAngle());
}

void Bird::useSkill()
{
      std::cout << "use bird's skill!" << std::endl;
}

