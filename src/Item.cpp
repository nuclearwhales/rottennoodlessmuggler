#include "Item.h"

namespace Rotten {

Item::Item(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite(parent, drawables) {}

Item::~Item() = default;

}
