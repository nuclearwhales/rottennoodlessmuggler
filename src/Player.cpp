#include "Player.h"

#include "GameScreen.h"

namespace Rotten {

Player::Player(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite({32,48},"smuggler",parent, drawables) {}

void Player::goLeft(PositionState ) {
    translate({-55, 0});
}

void Player::goRight(PositionState) {
    translate({55, 0});
}

void Player::moveUp(PositionState){
    translate({0, 24});
}

void Player::moveDown(PositionState){
    translate({0, -24});
}

void Player::takeAction() {}

}
