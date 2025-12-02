#include "game.h"

#include "config.h"
#include "entity/entity.h"
#include "entity/player.h"
#include "entity_pool/bullet_pool.h"
#include "entity_pool/enemy_pool.h"
#include "statistic.h"
#include "window/window.h"

#include "raylib.h"

#include <memory>
#include <string>

void Game::init() {
  status_ = Status::PRE_GAME;

  /* 初始化窗口 */
  window_ = std::make_unique<Window>(
      Config::Window::WIDTH, Config::Window::HEIGHT, Config::Window::TITLE);
  window_->set_fps(Config::Window::FPS); // 设置帧率

  /* 初始化统计数据 */
  Statistic::resetStatistics();

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
  enemy_manager_ = std::make_shared<EnemyManager>(
      std::move(enemy_pool_), Config::EnemyManager::SPAWN_INTERVAL);

  /* 创建子弹管理器 */
  std::unique_ptr<BulletPool> bullet_pool_ = std::make_unique<BulletPool>(
      Config::BulletPool::COUNT, Config::BulletPool::POSITION,
      Config::BulletPool::VELOCITY, Config::BulletPool::ACCELERATION,
      Config::BulletPool::RADIUS, Config::BulletPool::HP,
      Config::BulletPool::SCALE, Config::BulletPool::IMG_PATH,
      Config::BulletPool::SPEED);
  bullet_pool_->createEntities();
  bullet_manager_ = std::make_shared<BulletManager>(
      std::move(bullet_pool_), Config::BulletManager::SPAWN_INTERVAL, player_);

  /* 创建碰撞管理器 */
  collision_manager_ = std::make_unique<CollisionManager>(
      player_, enemy_manager_, bullet_manager_);
}

void Game::run() {
  while (!window_->shouldClose()) {
    window_->beginDrawing();            // 开始绘制
    window_->setBackgroundColor(BLACK); // 设置背景颜色
    window_->drawFPS(5, 5);             // 绘制帧率

    switch (status_) {
    case Status::PRE_GAME: {
      preGameScreen(); // 游戏开始前画面
      if (IsKeyPressed(KEY_ENTER)) {
        status_ = Status::RUNNING;
      }
      break;
    }
    case Status::RUNNING: {
      collision_manager_->handleCollisions(); // 处理碰撞

      /* 敌人生成与回收 */
      enemy_manager_->updateSpawner();
      enemy_manager_->returnToPool();

      /* 子弹生成与回收 */
      bullet_manager_->updateSpawner();
      bullet_manager_->returnToPool();

      /* 玩家输入处理、更新位置、绘制 */
      inputHandle();    // 输入处理
      updatePosition(); // 更新位置
      drawEntities();   // 绘制
      drawStatistics(); // 绘制统计信息
      drawPlayerHP();   // 绘制玩家血量

      if (shouldClose()) {
        status_ = Status::GAME_OVER;
      }
      break;
    }
    case Status::GAME_OVER: {
      gameOverScreen(); // 游戏结束画面
      if (IsKeyPressed(KEY_R)) {
        status_ = Status::RESTART;
      }
      break;
    }
    case Status::RESTART: {
      preGameScreen(); // 游戏开始前画面
      restart();       // 重新开始游戏
      if (IsKeyPressed(KEY_ENTER)) {
        status_ = Status::RUNNING;
      }
      break;
    }
    }

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

void Game::drawEntities() {
  player_->draw();
  enemy_manager_->drawEntities();
  bullet_manager_->drawEntities();
}

std::string Game::getScoreText() const {
  return "Score: " + std::to_string(Statistic::getScore());
}

std::string Game::getTimeText() const {
  Seconds time_passed = Statistic::getTimePassed();
  int     minutes     = static_cast<int>(time_passed.count()) / 60;
  int     seconds     = static_cast<int>(time_passed.count()) % 60;
  char    time_text[20];
  snprintf(time_text, sizeof(time_text), "Time: %02d:%02d", minutes, seconds);
  return std::string(time_text);
}

void Game::drawStatistics() {
  // 更新游戏已进行时间
  Statistic::updateTime(Clock::now());

  // 绘制分数
  std::string score_text = getScoreText();
  DrawText(score_text.c_str(), 10, 30, 40, WHITE);

  // 绘制时间
  std::string time_text_ = getTimeText();
  DrawText(time_text_.c_str(), 10, 70, 40, WHITE);
}

void Game::drawPlayerHP() {
  int hp = player_->get_hp();
  int r  = 30;
  DrawText("HP", 10, 110 + r, r, RED);
  for (int i = 0; i < hp; i++) {
    DrawCircle(3 * r + i * 2 * r, 110 + r, r, RED);
  }
}

bool Game::shouldClose() const {
  if (player_->get_hp() <= 0) {
    return true;
  }
  return false;
}

void Game::preGameScreen() {
  /* 游戏开始前画面 */
  std::string text;
  int         w;

  // 游戏标题
  text = "Plane War";
  w    = MeasureText(text.c_str(), 80);
  DrawText(text.c_str(), Config::Window::WIDTH / 2 - w / 2,
           Config::Window::HEIGHT / 2 - 160, 80, WHITE);

  // 按任意键开始游戏
  text = "Press Enter to Start";
  w    = MeasureText(text.c_str(), 40);
  DrawText(text.c_str(), Config::Window::WIDTH / 2 - w / 2,
           Config::Window::HEIGHT / 2, 40, WHITE);
}

void Game::gameOverScreen() {
  /* 游戏结束画面 */
  std::string text;
  int         w;

  // Game Over 标题
  text = "Game Over";
  w    = MeasureText(text.c_str(), 80);
  DrawText(text.c_str(), Config::Window::WIDTH / 2 - w / 2,
           Config::Window::HEIGHT / 2 - 100, 80, RED);

  // 退出提示
  text = "Press ESC to Exit";
  w    = MeasureText(text.c_str(), 40);
  DrawText(text.c_str(), Config::Window::WIDTH / 2 - w / 2,
           Config::Window::HEIGHT / 2, 40, WHITE);

  // Restart 提示
  text = "Press R to Restart";
  w    = MeasureText(text.c_str(), 40);
  DrawText(text.c_str(), Config::Window::WIDTH / 2 - w / 2,
           Config::Window::HEIGHT / 2 + 40, 40, WHITE);

  // 绘制最终分数及游戏时长
  text = getScoreText() + " (Final)";
  w    = MeasureText(text.c_str(), 40);
  DrawText(text.c_str(), Config::Window::WIDTH / 2 - w / 2,
           Config::Window::HEIGHT / 2 + 100, 40, BLUE);
  text = getTimeText();
  w    = MeasureText(text.c_str(), 40);
  DrawText(text.c_str(), Config::Window::WIDTH / 2 - w / 2,
           Config::Window::HEIGHT / 2 + 140, 40, BLUE);
}

void Game::restart() {
  /* 重新开始游戏 */
  Statistic::resetStatistics();
  player_->resetPlayer();
  enemy_manager_->resetEnemies();
  bullet_manager_->resetBullets();
}