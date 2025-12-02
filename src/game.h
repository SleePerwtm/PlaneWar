#pragma once

#include "entity/player.h"
#include "manager/bullet_manager.h"
#include "manager/collision_manager.h"
#include "manager/enemy_manager.h"
#include "window/window.h"

#include <memory>
#include <string>

enum class Status { PRE_GAME, RUNNING, GAME_OVER, RESTART };

class Game {
private:
  std::unique_ptr<Window>           window_;            // 窗口对象
  std::shared_ptr<Player>           player_;            // 玩家对象
  std::shared_ptr<EnemyManager>     enemy_manager_;     // 敌人管理器
  std::shared_ptr<BulletManager>    bullet_manager_;    // 子弹管理器
  std::unique_ptr<CollisionManager> collision_manager_; // 碰撞管理器

  Status status_;

  std::string getScoreText() const;
  std::string getTimeText() const;

public:
  Game()  = default;
  ~Game() = default;

  // 游戏初始化
  void init();
  // 游戏启动
  void run();

  // 输入处理
  void inputHandle();
  // 位置更新
  void updatePosition();
  // 绘制
  void drawEntities();

  // 绘制统计信息
  void drawStatistics();
  // 绘制玩家血量
  void drawPlayerHP();

  // 游戏需要结束
  bool shouldClose() const;

  // 游戏开始前画面
  void preGameScreen();
  // 游戏结束画面
  void gameOverScreen();

  // 重新开始游戏
  void restart();
};