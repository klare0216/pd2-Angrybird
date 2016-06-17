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
    std::cout<< "call setAwake ( " << g_body->GetGravityScale() << ")" << std::endl;
    g_body->SetAwake(flag);
    if (!flag) g_body->SetGravityScale(0);
    else g_body->SetGravityScale(1);

}

void GameItem::StartContact()
{
    ++ contact_num;
}

void GameItem::EndContact()
{
    -- contact_num;
}

void GameItem::deBug()
{
    std::cout << g_body->GetPosition().x << " , " << g_body->GetPosition().y << std::endl;
    std::cout << " awake?  "  << g_body->IsAwake() << std::endl ;
}

void GameItem::paint()
{
    b2Vec2 pos = g_body->GetPosition();
    //std::cout << "pos: " << pos.x << " , " << pos.y << std::endl;
    //std::cout << g_body->GetAngle() << std::endl;
    QPointF mappedPoint;
    mappedPoint.setX(((pos.x-g_size.x/2) * g_windowsize.width())/g_worldsize.width());
    mappedPoint.setY((1.0f - (pos.y + g_size.y/2)/g_worldsize.height()) * g_windowsize.height());
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
}

void GameItem::collide()
{
}

