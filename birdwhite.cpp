#include "birdwhite.h"

BirdWhite::BirdWhite(int qt_x, int qt_y, int qt_radius, QTimer *timer, QString image_path, b2World *world, QGraphicsScene *scene) :
    Bird(qt_x, qt_y, qt_radius, timer, image_path, world, scene),
    eggs_index(-1)
{
    int eggs_num = 3;
    for (int i = 0;i < eggs_num;++i)
    {
        itemList.push_back(new Egg(-100, -100, 12, timer, ":/image/egg.png", world, scene));
        itemList[0]->setShow(false);
        ++eggs_index;
   }
}

void BirdWhite::useSkill()
{
    std::cout << "use green bird's skill!" << std::endl;
    if (!is_skill_used)
    {
        int qt_x = QtX(g_body->GetPosition().x);
        int qt_y = QtY(g_body->GetPosition().y);
        itemList[eggs_index]->setQtPosition(qt_x, qt_y + 30);
        itemList[eggs_index]->setShow(true);
        static_cast<Egg * >(itemList[eggs_index])->setActive(true);
        if (eggs_index > 0)
        {
            --eggs_index;
        }else {
            is_skill_used = true;
        }
    }
}

int BirdWhite::type()
{
    return type_birdwhite;
}

