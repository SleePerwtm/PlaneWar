#pragma once

#include "entity/player.h"
#include "entity_pool/bullet_pool.h"
#include "entity_pool/enemy_pool.h"
#include "manager/bullet_manager.h"
#include "manager/enemy_manager.h"
#include "window/window.h"

#include <memory>

class Game {
private:
  std::unique_ptr<Window>        window_;         // 窗口对象
  std::shared_ptr<Player>        player_;         // 玩家对象
  std::unique_ptr<EnemyManager>  enemy_manager_;  // 敌人管理器
  std::unique_ptr<BulletManager> bullet_manager_; // 子弹管理器

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