#include "Player.h"

#include "Dumpster.h"
#include "GameScreen.h"
#include "Item.h"

namespace Rotten {

Player::Player(Dumpster* levelDumpster, Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite({32,48},"smuggler",parent, drawables) {
    this->levelDumpster = levelDumpster;
}

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

void Player::takeAction() {
    if(actualItem == nullptr){
        if(levelDumpster->item(positionIndex)){
            actualItem = levelDumpster->take(positionIndex);
            actualItem->drawables()->remove(*actualItem);
            actualItem->setParent(this);
            reset({32,48},"smuggler-with-item");
        }
    } else {
        // throw or save item;
    }
}

}
