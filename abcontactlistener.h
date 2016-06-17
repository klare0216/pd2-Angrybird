#ifndef ABCONTACTLISTENER_H
#define ABCONTACTLISTENER_H
#include <Box2D/Box2D.h>
#include <gameitem.h>
#include <iostream>
class abContactListener : public b2ContactListener
{
public:
    abContactListener();
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact * contact);
};

#endif // ABCONTACTLISTENER_H
