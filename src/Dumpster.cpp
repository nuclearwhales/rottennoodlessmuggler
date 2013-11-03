#include "Dumpster.h"
#include "Item.h"

#include <sstream>
#include <Utility/Configuration.h>
#include <Utility/Resource.h>

namespace Rotten {

Dumpster::Dumpster(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite(parent, drawables), _current(0) {
    Utility::Resource rs("data");
    std::istringstream in(rs.get("items.conf"));
    _conf = Utility::Configuration(in);
    CORRADE_INTERNAL_ASSERT(_conf.groupCount("item") > _current);
}

Item* Dumpster::next() {
    /* Dumpster empty */
    if(_current == _conf.groupCount("item")) return nullptr;

    /* Load info about current item from config file */
    auto itemData = _conf.group("item", _current);
    CORRADE_INTERNAL_ASSERT(itemData);
    auto imageData = _conf.group("images")->group(itemData->value("image"));
    CORRADE_INTERNAL_ASSERT(imageData);

    /* Populate the item */
    auto item = new Item(this, drawables());
    item->reset(imageData->value<Vector2i>("size"), imageData->value("file"));
    item->_contents = itemData->value("contents");
    item->_size = itemData->value<Int>("size");
    item->_value = itemData->value<Int>("value");

    /* Move to next item in the dumpster (nothing fancy now, just sequential) */
    ++_current;
    return item;
}

}
