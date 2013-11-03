#ifndef Rotten_Player_h
#define Rotten_Player_h

#include <Interconnect/Receiver.h>

#include "Sprite.h"

namespace Rotten {

class Player: public Sprite, public Interconnect::Receiver {
    public:
        explicit Player(Object2D* parent, SceneGraph::DrawableGroup2D* drawables);

        void goLeft();
        void goRight();
        void takeItem();
        void saveItem();
        void dropItem();
};

}

#endif
