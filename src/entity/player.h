#pragma once

#include "entity.h"

class Player : public Entity {
private:
public:
  Player();
  Player(const Player&)            = delete;
  Player& operator=(const Player&) = delete;
  ~Player()                        = default;

  // 重写更新位置的函数
  void updatePosition() override;
};