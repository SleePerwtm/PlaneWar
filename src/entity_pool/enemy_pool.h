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
  } default_;

public:
  EnemyPool(size_t pool_size, Vector2 position, Vector2 velocity,
            Vector2 acceleration, int radius, int hp, float scale,
            const char* texture_path);
  ~EnemyPool();

  // 创建实体
  void createEntities() override;
  // 更新位置
  void updateEntitiesPosition() override;
  // 绘制实体
  void drawEntities() override;
};