#include "player.h"
#include "../config.h"
#include "entity.h"
#include "raylib.h"

Player::Player()
    : Entity(Config::Player::position, Config::Player::velocity,
             Config::Player::acceleration, Config::Player::radius,
             Config::Player::hp, Config::Player::img_path,
             TextureType::UNIQUE) {}

void Player::draw() { DrawTexture(*texture_, position_.x, position_.y, WHITE); }