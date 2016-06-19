#include "enemy.h"

Enemy::Enemy(int qt_x, int qt_y, int q_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene) :
    GameItem(world)
{
     // Change unit fom qt to box2d
        // length
    float b_radius = q_radius * g_worldsize.width() / g_windowsize.width();
        // Set g_size
    g_size.Set(b_radius * 2, b_radius * 2);
        // pos
    float b_x =  qt_x * g_worldsize.width() / g_windowsize.width() ;
    float b_y = (1.0f - qt_y / g_windowsize.height())* g_worldsize.height() ;

    // Set pixmap
    g_pixmap.setPixmap(QPixmap(image_path).scaled(q_radius * 2, q_radius * 2));
    g_pixmap.setTransformationMode(Qt::SmoothTransformation);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);


    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(b_x, b_y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = b_radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = ENEMY_DENSITY;
    fixturedef.friction = ENEMY_FRICTION;
    fixturedef.restitution = ENEMY_RESTITUTION;
    // Set collide filter
        fixturedef.filter.categoryBits = ENEMY;
        fixturedef.filter.maskBits = DEFAULT | BIRD | ENEMY | BARRIER | EGG | LAND;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetSleepingAllowed(true);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));


    scene->addItem(&g_pixmap);
}

Enemy::~Enemy()
{
    std::cout << "delete !" << std::endl;
    while(itemList.length() != 0)
    {
        GameItem * tmp = itemList.last();
        itemList.pop_back();
        delete tmp;
    }
    g_world->DestroyBody(g_body);
    list_ptr->removeOne(this);
}

int * Enemy::e_score = NULL;
int Enemy::add_score = 10;
QList<GameItem *> * Enemy::list_ptr = NULL;

void Enemy::StartContact(GameItem * body)
{
    ++contact_num;
    if (contact_num == 2 || body->type() < 10)
    {
        *e_score = (*e_score + (add_score) * 100);
          std::cout << "score: " << *e_score << std::endl;
        deleteLater();
    }
}

int Enemy::type()
{
    return type_enemy;
}

