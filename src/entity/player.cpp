#include "player.h"

#include "raylib.h"

#include "../config.h"
#include "entity.h"

Player::Player()
    : Entity(Config::Player::POSITION, Config::Player::VELOCITY,
             Config::Player::ACCELERATION, Config::Player::RADIUS,
             Config::Player::HP, Config::Player::SCALE,
             Config::Player::IMG_PATH, TextureType::UNIQUE) {}

void Player::updatePosition() {
  /* 利用 raylib 中的 GetFrameTime() 函数，获取帧间间隔时间 */
  Vector2 target_pos;
  target_pos.x = position_.x + velocity_.x * GetFrameTime();
  target_pos.y = position_.y + velocity_.y * GetFrameTime();

  // 效果不好的代码，会导致飞机到屏幕边缘并按着组合键时，卡住不动
  // if (target_pos.x > 0 && target_pos.x <= GetScreenWidth() - 2 * radius_ &&
  //     target_pos.y > 0 && target_pos.y <= GetScreenHeight() - 2 * radius_)
  //   position_ = target_pos;

  /* 飞机在屏幕内才进行移动 */
  if (target_pos.x > 0 && target_pos.x <= GetScreenWidth() - 2 * radius_)
    position_.x = target_pos.x;
  if (target_pos.y > 0 && target_pos.y <= GetScreenHeight() - 2 * radius_)
    position_.y = target_pos.y;

  /* 更新飞机速度 */
  velocity_.x += acceleration_.x * GetFrameTime();
  velocity_.y += acceleration_.y * GetFrameTime();
}
