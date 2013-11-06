#include "Dumpster.h"
#include "Item.h"

#include <sstream>
#include <Utility/Configuration.h>
#include <Utility/Resource.h>

namespace Rotten {

namespace {
    constexpr Vector2i dumpsterSpriteOffset = Vector2i::yAxis(3);
    constexpr Vector2i dumpsterSpriteSize = Vector2i(48);
}

Dumpster::Dumpster(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Object2D(parent), _drawables(drawables), _dumpsterPositions{{-55, 22}, Vector2i::yAxis(46), {55, 22}}, _dumpsterItems{}, _current(0) {
    /* Dumpster sprites */
    for(Int i: {0, 1, 2}) {
        (_dumpsterSprites[i] = new Sprite(dumpsterSpriteSize, "dumpster-off", this, drawables))
            ->translate(_dumpsterPositions[i]+dumpsterSpriteOffset);
    }

    /* Item data */
    Utility::Resource rs("data");
    std::istringstream in(rs.get("items.conf"));
    _conf = Utility::Configuration(in);
    CORRADE_INTERNAL_ASSERT(_conf.groupCount("item") > _current);
}

bool Dumpster::next() {
    /* No more things available */
    if(_current == _conf.groupCount("item")) return false;

    /* Find empty dumpster */
    Int empty = -1;
    for(Int i = 0; i != 3; ++i) if(!_dumpsterItems[i]) {
        empty = i;
        break;
    }

    /* All dumpsters full */
    if(empty == -1) return false;

    /* Load info about current item from config file */
    auto itemData = _conf.group("item", _current);
    CORRADE_INTERNAL_ASSERT(itemData);
    auto imageData = _conf.group("images")->group(itemData->value("image"));
    CORRADE_INTERNAL_ASSERT(imageData);

    /* Populate the item */
    auto item = new Item(this);
    item->reset(imageData->value<Vector2i>("size"), imageData->value("file"));
    item->_contents = itemData->value("contents");
    item->_size = itemData->value<Int>("size");
    item->_value = itemData->value<Int>("value");

    /* Move to next item in the dumpster (nothing fancy now, just sequential) */
    ++_current;

    put(empty, item);
    return true;
}

Item* Dumpster::take(Int index) {
    CORRADE_INTERNAL_ASSERT(_dumpsterItems[index]);

    Item* i = _dumpsterItems[index];
    i->drawables()->remove(*i);
    i->setParent(nullptr);

    _dumpsterItems[index] = nullptr;
    _dumpsterSprites[index]->reset(dumpsterSpriteSize, "dumpster-off");

    return i;
}

void Dumpster::put(Int index, Item* i) {
    CORRADE_INTERNAL_ASSERT(!_dumpsterItems[index]);

    i->setTransformation(_dumpsterPositions[index]);
    i->setParent(this);
    _drawables->add(*i);

    _dumpsterItems[index] = i;
    _dumpsterSprites[index]->reset(dumpsterSpriteSize, "dumpster-on");
}

}
