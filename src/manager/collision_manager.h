#pragma once

#include "../entity/entity.h"
#include "../entity/player.h"
#include "../manager/bullet_manager.h"
#include "../manager/enemy_manager.h"

#include <memory>

class CollisionManager {
private:
  std::shared_ptr<Player>        player_;         // 玩家对象
  std::shared_ptr<EnemyManager>  enemy_manager_;  // 敌人管理器
  std::shared_ptr<BulletManager> bullet_manager_; // 子弹管理器
public:
  CollisionManager(std::shared_ptr<Player>        player,
                   std::shared_ptr<EnemyManager>  enemy_manager,
                   std::shared_ptr<BulletManager> bullet_manager);
  ~CollisionManager() = default;

  // 处理所有碰撞
  void handleCollisions();

  // 两对象池之间的碰撞检测
  template <class PoolType1, class PoolType2>
  void detectCollisions(PoolType1& pool1, PoolType2& pool2);

  // 某对象池与单个实体之间的碰撞检测
  template <class PoolType>
  void detectCollisionsWithEntity(PoolType& pool, Entity& entity);

  // 两个实体之间是否发生碰撞
  bool isColliding(const Entity& entity1, const Entity& entity2);
};