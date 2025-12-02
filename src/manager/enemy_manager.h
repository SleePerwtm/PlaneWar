#pragma once

#include "entity_manager.hpp"

#include "../entity/entity.h"
#include "../entity_pool/enemy_pool.h"

#include <memory>

class EnemyManager : public EntityManager<EnemyPool> {
private:
public:
  EnemyManager(std::unique_ptr<EnemyPool> enemy_pool,
               EntityManager::Seconds     spawn_interval);
  ~EnemyManager() = default;

  // 生成一个实体
  void spawnEntity() override;

  // 需要回收
  bool shouldReturnToPool(Entity& entity) const override;
  // 回收一个实体
  void returnToPool() override;
};