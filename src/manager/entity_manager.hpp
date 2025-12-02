#pragma once

#include "../entity/entity.h"
#include "raylib.h"

#include <chrono>
#include <memory>

template <class PoolType> class EntityManager {
public:
  using Clock     = std::chrono::steady_clock;
  using TimePoint = Clock::time_point;
  using Seconds   = std::chrono::duration<float>;

protected:
  std::unique_ptr<PoolType> pool_; // 实体对象池

  Seconds   spawn_interval_;  // 生成间隔时间
  TimePoint last_spawn_time_; // 上次生成时间点

public:
  EntityManager(std::unique_ptr<PoolType> pool, Seconds spawn_interval);
  ~EntityManager() = default;

  // 更新生成逻辑
  virtual void updateSpawner();

  // 生成一个实体
  virtual void spawnEntity() = 0;

  // 需要回收
  virtual bool shouldReturnToPool(Entity& entity) const = 0;
  // 回收一个实体
  virtual void returnToPool() = 0;

  // 碰撞检测（池里所有实体与指定实体的碰撞）
  virtual void checkCollisionsWith(Entity& other);

  // 绘制实体池中的实体
  virtual void drawEntities() const;
  // 更新实体池中的实体位置
  virtual void updateEntitiesPosition();

protected:
  // 是否与其他实体发生碰撞
  virtual bool isCollidingWith(const Entity& entity, const Entity& other);
  // 发生碰撞时执行的操作
  virtual void onCollision(Entity& entity, Entity& other) = 0;
};

template <class PoolType>
EntityManager<PoolType>::EntityManager(std::unique_ptr<PoolType> pool,
                                       Seconds                   spawn_interval)
    : pool_(std::move(pool)), spawn_interval_(spawn_interval) {
  last_spawn_time_ = Clock::now();
}

template <class PoolType> void EntityManager<PoolType>::updateSpawner() {
  TimePoint current_time = Clock::now();
  // 距离上次生成的时间间隔超过了 spawn_interval_
  if (current_time - last_spawn_time_ >= spawn_interval_) {
    spawnEntity();                   // 生成一个实体
    last_spawn_time_ = current_time; // 更新上次生成时间
  }
}

template <class PoolType>
void EntityManager<PoolType>::checkCollisionsWith(Entity& other) {
  for (auto& entity : pool_->get_entities()) {
    // 跳过不活跃的实体
    if (!entity->is_active()) {
      continue;
    }
    // 与 other 发生了碰撞
    if (isCollidingWith(*entity, other)) {
      onCollision(*entity, other); // 处理碰撞逻辑
    }
  }
}

template <class PoolType>
bool EntityManager<PoolType>::isCollidingWith(const Entity& entity,
                                              const Entity& other) {
  /* 获取并计算二者的半径与中心位置 */
  const float r1 = static_cast<float>(entity.get_radius());
  const float r2 = static_cast<float>(other.get_radius());
  // 此时获取的是左上角的坐标
  Vector2 pos1 = entity.get_position();
  Vector2 pos2 = other.get_position();
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

template <class PoolType> void EntityManager<PoolType>::drawEntities() const {
  pool_->drawEntities();
}

template <class PoolType>
void EntityManager<PoolType>::updateEntitiesPosition() {
  pool_->updateEntitiesPosition();
}