#include "Player.h"

namespace Rotten {

Player::Player(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite(parent, drawables) {}

void Player::goLeft(PositionState) {}

void Player::goRight(PositionState) {}

void Player::takeAction() {}

}
