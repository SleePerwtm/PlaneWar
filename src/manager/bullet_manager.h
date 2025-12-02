#pragma once

#include "../entity/player.h"
#include "../entity_pool/bullet_pool.h"
#include "entity_manager.hpp"

#include <memory>

class BulletManager : public EntityManager<BulletPool> {
private:
  std::shared_ptr<Player> player_; // 玩家对象指针
public:
  BulletManager(std::unique_ptr<BulletPool> bullet_pool,
                EntityManager::Seconds      spawn_interval,
                std::shared_ptr<Player>     player);
  ~BulletManager() = default;

  // 生成一个实体
  void spawnEntity() override;

  // 需要回收
  bool shouldReturnToPool(Entity& entity) const override;
  // 回收一个实体
  void returnToPool() override;

private:
  // 发生碰撞时执行的操作
  void onCollision(Entity& entity, Entity& other) override;
};