#pragma once

#include "entity_pool.h"

#include "raylib.h"

#include <cstddef>

class BulletPool : public EntityPool {
private:
  struct BulletData {
    Vector2     position;
    Vector2     velocity;
    Vector2     acceleration;
    int         radius;
    int         hp;
    float       scale;
    const char* texture_path;

    int speed;
  } default_;

public:
  BulletPool(size_t pool_size, Vector2 position, Vector2 velocity,
             Vector2 acceleration, int radius, int hp, float scale,
             const char* texture_path, int speed);
  ~BulletPool();

  // 创建实体
  void createEntities() override;
};