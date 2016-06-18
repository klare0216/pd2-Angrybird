#include "birdblue.h"

BirdBlue::BirdBlue(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene) :
    Bird::Bird(qt_x, qt_y, qt_radius, timer, image_path, world, scene)
{
    itemList.push_back(new Bird(qt_x, qt_y, qt_radius, timer, image_path, world, scene));
    itemList[0]->setShow(false);
    itemList.push_back(new Bird(qt_x, qt_y, qt_radius, timer,  image_path, world, scene));
    itemList[1]->setShow(false);
}

void BirdBlue::useSkill()
{
    std::cout << "use blue bird's skill!" << std::endl;
    if (!is_skill_used)
    {
        int qt_x = GameItem::QtX(g_body->GetPosition().x);
        int qt_y = GameItem::QtY(g_body->GetPosition().y);
        itemList[0]->setQtPosition(qt_x, qt_y);
        itemList[1]->setQtPosition(qt_x, qt_y);
        itemList[0]->setShow(true);
        itemList[1]->setShow(true);
         is_skill_used = true;
    }
}

int BirdBlue::type()
{
    return type_birdblue;
}
