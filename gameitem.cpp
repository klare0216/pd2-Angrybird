#include "gameitem.h"

#include <iostream>

GameItem::GameItem(b2World *world):
    g_body(NULL),
    g_world(world),
    contact_num(0)
{
}

GameItem::~GameItem()
{
    std::cout << "delete !" << std::endl;
    while(itemList.length() != 0)
    {
        GameItem * tmp = itemList.last();
        itemList.pop_back();
        delete tmp;
    }
    g_world->DestroyBody(g_body);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::g_worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize)
{
    g_worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::setAwake(bool flag)
{
    //std::cout<< "call setAwake ( " << g_body->GetGravityScale() << ")" << std::endl;
   // g_body->SetAwake(flag);
    if (!flag) g_body->SetGravityScale(0);
    else g_body->SetGravityScale(1);
}

void GameItem::setShow(bool flag)
{
    if (flag)
    {
        setQtPosition(g_qtpos.x,g_qtpos.y);
        setAwake(true);
    } else {
        setQtPosition(-500,-500);
        setAwake(false);
    }
}

void GameItem::setQtPosition(int qt_x, int qt_y)
{
    g_qtpos.x = qt_x;
    g_qtpos.y = qt_y;
    float b_x = qt_x * g_worldsize.width() / g_windowsize.width();
    float b_y = (1.0f - qt_y / g_windowsize.height())* g_worldsize.height() ;
    g_body->SetTransform(b2Vec2(b_x, b_y),g_body->GetAngle());
}

bool GameItem::isStop()
{
   if (g_body->GetLinearVelocity() == b2Vec2(0,0))
   {
       return true;
   }
   return false;
}

b2Vec2 GameItem::getB2Pos()
{
    return g_body->GetPosition();
}

void GameItem::StartContact(GameItem *)
{
    ++ contact_num;
}

void GameItem::EndContact()
{
    -- contact_num;
}

int GameItem::QtX(float b_x)
{
    return (b_x* g_windowsize.width())/g_worldsize.width();
}

int GameItem::QtY(float b_y)
{
    return (1.0f - b_y/g_worldsize.height()) * g_windowsize.height();
}

void GameItem::deBug()
{
    std::cout << g_body->GetPosition().x << " , " << g_body->GetPosition().y << std::endl;
    std::cout << " awake?  "  << g_body->IsAwake() << std::endl ;
}

void GameItem::paint()
{
    b2Vec2 pos = g_body->GetPosition();
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.x/2) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y + g_size.y/2)/g_worldsize.height()) * g_windowsize.height());

    //set qtpos
    g_qtpos.x = mappedPoint.rx();
    g_qtpos.y = mappedPoint.ry();

    // set g_pixmap
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
}
