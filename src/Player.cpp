#include "Player.h"

#include "Dumpster.h"
#include "GameScreen.h"
#include "Item.h"
#include "Bag.h"

namespace Rotten {

namespace {
    constexpr Vector2i playerSpriteSize = {32, 48};
}

Player::Player(Bag* bag, Dumpster* dumpster, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite(playerSpriteSize,"smuggler",parent, drawables), bag(bag), dumpster(dumpster) {}

void Player::goLeft(PositionState ) {
    --positionIndex;
    translate({-55, 0});
}

void Player::goRight(PositionState) {
    ++positionIndex;
    translate({55, 0});
}

void Player::moveUp(PositionState){
    translate({0, 24});
}

void Player::moveDown(PositionState){
    translate({0, -24});
}

void Player::grab() {
    /* Take */
    if(!actualItem) {
        if(!dumpster->item(positionIndex)) return;

        actualItem = dumpster->take(positionIndex);
        actualItem->setParent(this);
        reset(playerSpriteSize, "smuggler-with-item");

    /* Put */
    } else {
        if(dumpster->item(positionIndex)) return;

        dumpster->put(positionIndex, actualItem);
        actualItem = nullptr;
        reset(playerSpriteSize, "smuggler");
    }
}

void Player::save() {
    if(!actualItem) return;

    /* Put the item into bag, if possible */
    if(!bag->put(actualItem)) return;
    actualItem = nullptr;
    reset(playerSpriteSize, "smuggler");

    /* Arrival of next item in the dumpster */
    dumpster->next();
}

}
