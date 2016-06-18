#include "abcontactlistener.h"

abContactListener::abContactListener()
{

}

void abContactListener::BeginContact(b2Contact *contact)
{
    void * body_A = contact->GetFixtureA()->GetBody()->GetUserData();
    void * body_B = contact->GetFixtureB()->GetBody()->GetUserData();

    if (body_A && body_B)
    {
        //std::cout << body_A << "," << body_B << std::endl;
       static_cast<GameItem *>(body_A)->StartContact(static_cast<GameItem *>(body_B));
       static_cast<GameItem *>(body_B)->StartContact(static_cast<GameItem *>(body_A));
    }
}

void abContactListener::EndContact(b2Contact *contact)
{
    void * body_A = contact->GetFixtureA()->GetBody()->GetUserData();
     void * body_B = contact->GetFixtureB()->GetBody()->GetUserData();
   //  std::cout << body_A << "," << body_B << std::endl;

     //std::cout << "collide! " << std::endl;
    if (body_A)
    {
       static_cast<GameItem *>(body_A)->EndContact();
        //std::cout << "A end contact! " << std::endl;
    }
    if (body_B)
    {
       static_cast<GameItem *>(body_B)->EndContact();
      //  std::cout << "B end contact! " << std::endl;
    }
}
