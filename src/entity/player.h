#pragma once

#include "entity.h"

#include "raylib.h"

class Player : public Entity {
private:
public:
  Player(Vector2 pos, Vector2 vel, Vector2 acc, int rad, int hp, float scale,
         const char* path, TextureType type);
  Player(const Player&)            = delete;
  Player& operator=(const Player&) = delete;
  ~Player()                        = default;

  // 重写更新位置的函数
  void updatePosition() override;
};