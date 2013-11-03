#ifndef Rotten_Dumpster_h
#define Rotten_Dumpster_h

#include <Utility/Configuration.h>

#include "Sprite.h"

namespace Rotten {

class Item;

class Dumpster: public Sprite {
    public:
        explicit Dumpster(Object2D* parent, SceneGraph::DrawableGroup2D* drawables);

        Item* next();

    private:
        Utility::Configuration _conf;
        UnsignedInt _current;
};

}

#endif
