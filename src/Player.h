#ifndef Rotten_Player_h
#define Rotten_Player_h

#include <Interconnect/Receiver.h>

#include "Sprite.h"

namespace Rotten {

class Bag;
class Dumpster;
class Item;

enum class PositionState: UnsignedByte;

class Player: public Sprite, public Interconnect::Receiver {
    public:
        explicit Player(Bag* bag, Dumpster* levelDumpster, Object2D* parent, SceneGraph::DrawableGroup2D* drawables);

        void goLeft(PositionState);
        void goRight(PositionState);
        void moveUp(PositionState);
        void moveDown(PositionState);

        void grab();
        void save();

    private:
        Bag* bag;
        Dumpster* dumpster;
        Item* actualItem=nullptr;
        Int positionIndex=1;
};

}

#endif
