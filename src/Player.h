#ifndef Rotten_Player_h
#define Rotten_Player_h

#include <Interconnect/Receiver.h>

#include "Sprite.h"

namespace Rotten {

class Player: public Interconnect::Receiver{

public:
    void goLeft();
    void goRight();
    void takeItem();
    void saveItem();
    void dropItem();

private:
    Sprite playerSprite;
    Vector2 position;
};

}

#endif
