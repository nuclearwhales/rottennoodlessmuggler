#ifndef Rotten_Item_h
#define Rotten_Item_h

#include "Sprite.h"

namespace Rotten {

class Item: public Sprite {
    friend class Dumpster;

    public:
        explicit Item(Object2D* parent, SceneGraph::DrawableGroup2D* drawables = nullptr);

        ~Item();

        std::string contents() const { return _contents; }
        Int value() const { return _value; }
        Int size() const { return _size; }

    private:
        std::string _contents;
        Int _value;
        Int _size;
};

}

#endif
