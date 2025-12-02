#include "collision_manager.h"

#include "../entity/entity.h"
#include "../entity/player.h"
#include "../manager/bullet_manager.h"
#include "../manager/enemy_manager.h"
#include "../statistic.h"

#include "raylib.h"

CollisionManager::CollisionManager(
    std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy_manager,
    std::shared_ptr<BulletManager> bullet_manager)
    : player_(player), enemy_manager_(enemy_manager),
      bullet_manager_(bullet_manager) {}

void CollisionManager::handleCollisions() {
  // 玩家与敌人之间的碰撞检测
  detectCollisionsWithEntity(enemy_manager_->get_pool(), *player_);
  // 子弹与敌人之间的碰撞检测
  detectCollisions<BulletPool, EnemyPool>(bullet_manager_->get_pool(),
                                          enemy_manager_->get_pool());
}

template <class PoolType1, class PoolType2>
void CollisionManager::detectCollisions(PoolType1& pool1, PoolType2& pool2) {
  for (auto& entity1 : pool1.get_entities()) {
    // 跳过不活跃的实体
    if (!entity1->is_active()) {
      continue;
    }
    for (auto& entity2 : pool2.get_entities()) {
      // 跳过不活跃的实体
      if (!entity2->is_active()) {
        continue;
      }
      // 发生了碰撞
      if (isColliding(*entity1, *entity2)) {
        // 处理碰撞逻辑
        entity1->damage(1);
        entity2->damage(1);
        Statistic::addScore(10); // 碰撞得分
      }
    }
  }
}

template <class PoolType>
void CollisionManager::detectCollisionsWithEntity(PoolType& pool,
                                                  Entity&   entity) {
  for (auto& e : pool.get_entities()) {
    // 跳过不活跃的实体
    if (!e->is_active()) {
      continue;
    }
    // 发生了碰撞
    if (isColliding(*e, entity)) {
      // 处理碰撞逻辑
      e->damage(1);
      entity.damage(1);
    }
  }
}

bool CollisionManager::isColliding(const Entity& entity1,
                                   const Entity& entity2) {
  /* 获取并计算二者的半径与中心位置 */
  const float r1 = static_cast<float>(entity1.get_radius());
  const float r2 = static_cast<float>(entity2.get_radius());
  // 此时获取的是左上角的坐标
  Vector2 pos1 = entity1.get_position();
  Vector2 pos2 = entity2.get_position();
  // 在左上角的基础上加上半径获得中心坐标
  pos1.x += r1;
  pos1.y += r1;
  pos2.x += r2;
  pos2.y += r2;
  // 计算横纵坐标差值
  const float dx = pos1.x - pos2.x;
  const float dy = pos1.y - pos2.y;
  // 计算距离的平方
  const float distanceSquare = dx * dx + dy * dy;
  // 半径之和
  const float radiusSum = r1 + r2;

  /* 比较距离的平方与半径之和的平方 */
  return distanceSquare <= radiusSum * radiusSum;
}