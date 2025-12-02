#pragma once

#include "entity/player.h"
#include "entity_pool/enemy_pool.h"
#include "manager/enemy_manager.h"
#include "window/window.h"

#include <memory>

class Game {
private:
  std::unique_ptr<Window>       window_;        // 窗口对象
  std::unique_ptr<Player>       player_;        // 玩家对象
  std::unique_ptr<EnemyPool>    enemy_pool_;    // 敌人对象池
  std::unique_ptr<EnemyManager> enemy_manager_; // 敌人管理器

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
  void draw();
};