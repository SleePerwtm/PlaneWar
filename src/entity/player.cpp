#include "player.h"

#include "raylib.h"

#include "../config.h"
#include "entity.h"

Player::Player()
    : Entity(Config::Player::POSITION, Config::Player::VELOCITY,
             Config::Player::ACCELERATION, Config::Player::RADIUS,
             Config::Player::HP, Config::Player::IMG_PATH,
             TextureType::UNIQUE) {}

void Player::draw() { DrawTexture(*texture_, position_.x, position_.y, WHITE); }