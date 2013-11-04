#include "Player.h"

namespace Rotten {

Player::Player(Object2D* parent, SceneGraph::DrawableGroup2D* drawables): Sprite({32,48},"smuggler",parent, drawables) {}

void Player::goLeft(PositionState) {}

void Player::goRight(PositionState) {}

void Player::takeAction() {}

}
