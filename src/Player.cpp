#include "Player.h"

namespace Rotten {

Player::Player(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite(parent, drawables) {}

void Player::dropItem() {}

void Player::goLeft() {}

void Player::goRight() {}

void Player::saveItem() {}

void Player::takeItem() {}

}
