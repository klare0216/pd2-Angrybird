#include "land.h"

Land::Land(int qt_x, int qt_y, int qt_w, int qt_h, QString image_path, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Change unit fom qt to box2d
        // length
    float b_w = qt_w * g_worldsize.width() / g_windowsize.width();
    float b_h = qt_h * g_worldsize.height() / g_windowsize.height();
        // Set g_size
    g_size.Set(b_w, b_h);
        // pos
    float b_x =  qt_x * g_worldsize.width() / g_windowsize.width() ;
    float b_y = (1.0f - qt_y / g_windowsize.height())* g_worldsize.height() ;

    // Set pixmap
    g_pixmap.setPixmap(QPixmap(image_path).scaled(qt_w, qt_h));
    g_pixmap.setTransformationMode(Qt::SmoothTransformation);
    g_size.Set(b_w, b_h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(b_x, b_y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(b_w/2, b_h/2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = 9.0f;
    fixturedef.friction = 1.0f;
    // Set collide filter
        fixturedef.filter.categoryBits = LAND;
        fixturedef.filter.maskBits = DEFAULT | BIRD | ENEMY | BARRIER | EGG | LAND;
    g_body->CreateFixture(&fixturedef);


    scene->addItem(&g_pixmap);
    paint();
}

int Land::type()
{
    return type_land;
}
