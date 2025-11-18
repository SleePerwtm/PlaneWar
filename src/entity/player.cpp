#include "player.h"

#include "raylib.h"

#include "../config.h"
#include "entity.h"

Player::Player()
    : Entity(Config::Player::POSITION, Config::Player::VELOCITY,
             Config::Player::ACCELERATION, Config::Player::RADIUS,
             Config::Player::HP, Config::Player::IMG_PATH,
             TextureType::UNIQUE) {}

void Player::updatePosition() {
  /* 利用 raylib 中的 GetFrameTime() 函数，获取帧间间隔时间 */
  Vector2 target_pos;
  target_pos.x = position_.x + velocity_.x * GetFrameTime();
  target_pos.y = position_.y + velocity_.y * GetFrameTime();
  if (target_pos.x > 0 && target_pos.x <= GetScreenWidth() - 2 * radius_)
    position_.x = target_pos.x;
  if (target_pos.y > 0 && target_pos.y <= GetScreenHeight() - 2 * radius_)
    position_.y = target_pos.y;

  velocity_.x += acceleration_.x * GetFrameTime();
  velocity_.y += acceleration_.y * GetFrameTime();
}

void Player::draw() { DrawTexture(*texture_, position_.x, position_.y, WHITE); }