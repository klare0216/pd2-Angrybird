#include "egg.h"

Egg::Egg(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path,  b2World *world, QGraphicsScene *scene) :
    GameItem(world)
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
    fixturedef.density = EGG_DENSITY;
    fixturedef.friction = EGG_FRICTION;
    fixturedef.restitution = EGG_RESTITUTION;
        // Set collide filter
    fixturedef.filter.categoryBits = EGG;
    fixturedef.filter.maskBits = DEFAULT | ENEMY | EGG | LAND;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetSleepingAllowed(true);
    g_body->SetActive(false);


    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

int Egg::type()
{
    return type_egg;
}

void Egg::setActive(bool flag)
{
    g_body->SetActive(flag);
}
