#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>

#include <QPainter>
#include <QTransform>
#include <QtMath>

enum Category {
    DEFAULT = 0x0001,
    BIRD = 0x0002,
    ENEMY = 0x0004,
    BARRIER = 0x0008,
    EGG = 0x0010,
    LAND = 0x0020
};

class GameItem : public QObject
{
    Q_OBJECT
public:
    GameItem(b2World *world);
    virtual ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    void setAwake(bool flag);
    void setShow(bool flag);
    void setQtPosition(int qt_x, int qt_y);
    virtual int type() = 0;
    virtual void StartContact(GameItem *);
    virtual void EndContact();

    // For Unit
    static int QtX(float b_x);
    static int QtY(float b_y);

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
    b2Vec2 g_qtpos;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;

    // For collide
    int contact_num;

    // For item
    QList<GameItem *> itemList;

    // For GameItem type
        // birds
    static  const int type_bird = 0;
    static  const int type_birdblack = 1;
    static  const int type_birdgreen = 2;
    static  const int type_birdblue = 3;
    static  const int type_birdwhite= 4;
    static  const int type_birdyellow = 5;
        // barrier
    static  const int type_barrier = 10;
        // enemy
    static  const int type_enemy = 20;
        // egg
    static  const int type_egg = 30;
        // land
    static  const int type_land = 40;
    // For categoryBits

};

#endif // GAMEITEM_H
