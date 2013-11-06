#ifndef Rotten_Bag_h
#define Rotten_Bag_h

#include "Sprite.h"

namespace Rotten {

class Item;

class Bag: public Sprite {
    public:
        explicit Bag(Object2D* parent, SceneGraph::DrawableGroup2D* drawables);

        ~Bag();

        bool put(Item* item);

        std::vector<Item*>& items() { return _items; }

    private:
        std::vector<Item*> _items;
};

}

#endif
