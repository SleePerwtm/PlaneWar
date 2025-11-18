#pragma once

#include "entity/player.h"
#include "window/window.h"

#include <memory>

class Game {
private:
  std::unique_ptr<Window> window_; // 窗口对象
  std::unique_ptr<Player> player_; // 玩家对象

public:
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