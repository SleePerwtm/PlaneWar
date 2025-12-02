#include "game.h"

#include "config.h"
#include "entity/entity.h"
#include "entity/player.h"
#include "entity_pool/bullet_pool.h"
#include "entity_pool/enemy_pool.h"
#include "window/window.h"

#include "raylib.h"

#include <memory>

void Game::init() {
  /* 初始化窗口 */
  window_ = std::make_unique<Window>(
      Config::Window::WIDTH, Config::Window::HEIGHT, Config::Window::TITLE);
  window_->set_fps(Config::Window::FPS); // 设置帧率

  /* 创建玩家实体 */
  player_ = std::make_shared<Player>(
      Config::Player::POSITION, Config::Player::VELOCITY,
      Config::Player::ACCELERATION, Config::Player::RADIUS, Config::Player::HP,
      Config::Player::SCALE, Config::Player::IMG_PATH, TextureType::UNIQUE);

  /* 创建敌人管理器 */
  std::unique_ptr<EnemyPool> enemy_pool_ = std::make_unique<EnemyPool>(
      Config::EnemyPool::COUNT, Config::EnemyPool::POSITION,
      Config::EnemyPool::VELOCITY, Config::EnemyPool::ACCELERATION,
      Config::EnemyPool::RADIUS, Config::EnemyPool::HP,
      Config::EnemyPool::SCALE, Config::EnemyPool::IMG_PATH,
      Config::EnemyPool::MIN_SPEED, Config::EnemyPool::MAX_SPEED);
  enemy_pool_->createEntities();
  enemy_manager_ = std::make_unique<EnemyManager>(
      std::move(enemy_pool_), Config::EnemyManager::SPAWN_INTERVAL);

  /* 创建子弹管理器 */
  std::unique_ptr<BulletPool> bullet_pool_ = std::make_unique<BulletPool>(
      Config::BulletPool::COUNT, Config::BulletPool::POSITION,
      Config::BulletPool::VELOCITY, Config::BulletPool::ACCELERATION,
      Config::BulletPool::RADIUS, Config::BulletPool::HP,
      Config::BulletPool::SCALE, Config::BulletPool::IMG_PATH,
      Config::BulletPool::SPEED);
  bullet_pool_->createEntities();
  bullet_manager_ = std::make_unique<BulletManager>(
      std::move(bullet_pool_), Config::EnemyManager::SPAWN_INTERVAL, player_);
}

void Game::run() {
  while (!window_->shouldClose()) {
    window_->beginDrawing();            // 开始绘制
    window_->setBackgroundColor(BLACK); // 设置背景颜色
    window_->drawFPS(5, 5);             // 绘制帧率

    /* 敌人生成与回收 */
    enemy_manager_->updateSpawner();
    enemy_manager_->returnToPool();

    /* 子弹生成与回收 */
    bullet_manager_->updateSpawner();
    bullet_manager_->returnToPool();

    /* 玩家输入处理、更新位置、绘制 */
    inputHandle();    // 输入处理
    updatePosition(); // 更新位置
    draw();           // 绘制

    window_->endDrawing(); // 结束绘制
  }
  window_->close(); // 关闭窗口
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
  enemy_manager_->updateEntitiesPosition();
  bullet_manager_->updateEntitiesPosition();
}

void Game::draw() {
  player_->draw();
  enemy_manager_->drawEntities();
  bullet_manager_->drawEntities();
}