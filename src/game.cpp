#include "game.h"

#include "config.h"
#include "entity/entity.h"
#include "entity/player.h"
#include "raylib.h"
#include "window/window.h"

void Game::init() {
  /* 初始化窗口 */
  window_ = std::make_unique<Window>(
      Config::Window::WIDTH, Config::Window::HEIGHT, Config::Window::TITLE);
  window_->set_fps(Config::Window::FPS); // 设置帧率

  /* 创建玩家实体 */
  player_ = std::make_unique<Player>(
      Config::Player::POSITION, Config::Player::VELOCITY,
      Config::Player::ACCELERATION, Config::Player::RADIUS, Config::Player::HP,
      Config::Player::SCALE, Config::Player::IMG_PATH, TextureType::UNIQUE);

  /* 创建敌人对象池 */
  enemy_pool_ = std::make_unique<EnemyPool>(
      Config::EnemyPool::COUNT, Config::EnemyPool::POSITION,
      Config::EnemyPool::VELOCITY, Config::EnemyPool::ACCELERATION,
      Config::EnemyPool::RADIUS, Config::EnemyPool::HP,
      Config::EnemyPool::SCALE, Config::EnemyPool::IMG_PATH,
      Config::EnemyPool::MIN_SPEED, Config::EnemyPool::MAX_SPEED);
  enemy_pool_->createEntities();
  enemy_pool_->setRandomInitialState();
}

void Game::run() {
  while (!window_->shouldClose()) {
    window_->beginDrawing();
    window_->setBackgroundColor(BLACK);
    window_->drawFPS(5, 5);

    inputHandle();
    updatePosition();
    draw();

    window_->endDrawing();
  }
  window_->close();
}

void Game::inputHandle() {
  /* 获取前一帧的玩家速度 */
  Vector2 player_velocity_ = player_->get_velocity();

  /* 检测到按键按下需要处理的逻辑 */
  if (IsKeyPressed(Config::Keyboard::UP))
    player_velocity_.y -= Config::Player::MOVE_VELOCITY.y;
  if (IsKeyPressed(Config::Keyboard::DOWN))
    player_velocity_.y += Config::Player::MOVE_VELOCITY.y;
  if (IsKeyPressed(Config::Keyboard::LEFT))
    player_velocity_.x -= Config::Player::MOVE_VELOCITY.x;
  if (IsKeyPressed(Config::Keyboard::RIGHT))
    player_velocity_.x += Config::Player::MOVE_VELOCITY.x;

  /* 检测到按键松开需要处理的逻辑 */
  if (IsKeyReleased(Config::Keyboard::UP))
    player_velocity_.y += Config::Player::MOVE_VELOCITY.y;
  if (IsKeyReleased(Config::Keyboard::DOWN))
    player_velocity_.y -= Config::Player::MOVE_VELOCITY.y;
  if (IsKeyReleased(Config::Keyboard::LEFT))
    player_velocity_.x += Config::Player::MOVE_VELOCITY.x;
  if (IsKeyReleased(Config::Keyboard::RIGHT))
    player_velocity_.x -= Config::Player::MOVE_VELOCITY.x;

  /* 更新玩家当前帧速度 */
  player_->set_velocity(player_velocity_);
}

void Game::updatePosition() {
  player_->updatePosition();
  enemy_pool_->updateEntitiesPosition();
}

void Game::draw() {
  player_->draw();
  enemy_pool_->drawEntities();
}