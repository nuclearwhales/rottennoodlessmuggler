#ifndef Rotten_Player_h
#define Rotten_Player_h

#include <Interconnect/Receiver.h>

#include "Sprite.h"

namespace Rotten {

enum class PositionState: UnsignedByte;

class Player: public Sprite, public Interconnect::Receiver {
    public:
        explicit Player(Object2D* parent, SceneGraph::DrawableGroup2D* drawables);

        void goLeft(PositionState);
        void goRight(PositionState);
        void takeAction();
};

}

#endif
