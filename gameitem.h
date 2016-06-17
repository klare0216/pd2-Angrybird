#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>


class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    virtual ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    virtual void setAwake(bool flag);
    virtual void StartContact();
    virtual void EndContact();
    // For DeBug
    void virtual deBug();

public slots:
    void paint();
    virtual void collide();

protected:
    // For Contact
    b2Body *g_body;
    QGraphicsPixmapItem g_pixmap;
    b2Vec2  g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;
    // For collide
    int contact_num;


};

#endif // GAMEITEM_H
