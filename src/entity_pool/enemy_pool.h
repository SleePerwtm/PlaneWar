#pragma once

#include "entity_pool.h"

#include "raylib.h"

#include <cstddef>

class EnemyPool : public EntityPool {
private:
  struct EnemyData {
    Vector2     position;
    Vector2     velocity;
    Vector2     acceleration;
    int         radius;
    int         hp;
    float       scale;
    const char* texture_path;

    int min_velocity;
    int max_velocity;
  } default_;

public:
  EnemyPool(size_t pool_size, Vector2 position, Vector2 velocity,
            Vector2 acceleration, int radius, int hp, float scale,
            const char* texture_path, int max_velocity, int min_velocity);
  ~EnemyPool();

  // 创建实体
  void createEntities() override;
  // 获取随机位置
  Vector2 getRandomPosition() const;
  // 获取随机速度
  Vector2 getRandomVelocity() const;
  // 设置随机初始状态
  void setRandomInitialState();
};