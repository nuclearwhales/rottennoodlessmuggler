#include "Bag.h"

#include "Item.h"

namespace Rotten {

Bag::Bag(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite(Vector2i(32), "bag", parent, drawables) {}

Bag::~Bag() = default;

bool Bag::put(Item* item) {
    item->setParent(this)
        .setTransformation({});
    _items.push_back(item);

    return true;
}

}
