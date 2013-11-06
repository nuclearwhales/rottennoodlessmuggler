#ifndef Rotten_Dumpster_h
#define Rotten_Dumpster_h

#include <Utility/Configuration.h>

#include "Sprite.h"

namespace Rotten {

class Item;

class Dumpster: public Object2D {
    public:
        explicit Dumpster(Object2D* parent, SceneGraph::DrawableGroup2D* drawables);

        bool next();

        bool item(Int index){return _dumpsterItems[index];}

        Item* take(Int index);

        void put(Int index, Item* item);

    private:
        SceneGraph::DrawableGroup2D* _drawables;
        const Vector2i _dumpsterPositions[3];
        Sprite* _dumpsterSprites[3];
        Item* _dumpsterItems[3];

        Utility::Configuration _conf;
        UnsignedInt _current;
};

}

#endif
