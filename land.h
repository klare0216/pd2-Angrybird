#ifndef LAND_H
#define LAND_H

#include <gameitem.h>
#include <QGraphicsScene>

class Land : public GameItem
{
public:
    Land(int x, int y, int w, int h, QString image_path, b2World *world, QGraphicsScene *scene);
};

#endif // LAND_H
