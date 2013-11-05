#ifndef Rotten_Player_h
#define Rotten_Player_h

#include <Interconnect/Receiver.h>

#include "Sprite.h"

namespace Rotten {

class Item;

class Dumpster;

enum class PositionState: UnsignedByte;

class Player: public Sprite, public Interconnect::Receiver {
    public:
        explicit Player(Dumpster* levelDumpster,Object2D* parent, SceneGraph::DrawableGroup2D* drawables);

        void goLeft(PositionState);
        void goRight(PositionState);
        void moveUp(PositionState);
        void moveDown(PositionState);
        void takeAction();

    private:
        Dumpster* levelDumpster;
        Item* actualItem=nullptr;
        Int positionIndex=1;
};

}

#endif
