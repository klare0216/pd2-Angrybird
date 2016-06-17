#include "barrier.h"

Barrier::Barrier(int qt_x, int qt_y, int qt_w, int qt_h, float angle, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene) : GameItem(world)
{
    // For debug
    // std::cout << "create barrier!" << std::endl;

    // Change unit fom qt to box2d
        // length
    float b_w = qt_w * g_worldsize.width() / g_windowsize.width();
    float b_h = qt_h * g_worldsize.height() / g_windowsize.height();
         // Setting g_size
    g_size.Set(b_w, b_h);
         // pos
    float b_x =  qt_x * g_worldsize.width() / g_windowsize.width();
    float b_y = (1.0f - qt_y / g_windowsize.height())* g_worldsize.height();
    float rad = angle * 3.14159265f / 180.0f;

    // Set pixmap
    g_pixmap.setPixmap(QPixmap(image_path).scaled(qt_w, qt_h));
    g_pixmap.setTransformationMode(Qt::SmoothTransformation);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(b_x, b_y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(b_w / 2, b_h / 2);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density =  BERRIER_DENSITY;
    fixturedef.friction =  BERRIER_FRICTION;
    fixturedef.restitution =  BERRIER_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetTransform(g_body->GetPosition(), rad);
    //g_body->SetSleepingAllowed(true);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}
