#pragma once

#include "../entity/entity.h"

#include "../config.h"
#include <memory>

template <class PoolType> class EntityManager {
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

  // 绘制实体池中的实体
  virtual void drawEntities() const;
  // 更新实体池中的实体位置
  virtual void updateEntitiesPosition();

  // 获取实体池的引用
  PoolType&       get_pool();
  const PoolType& get_pool() const;
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

template <class PoolType> void EntityManager<PoolType>::drawEntities() const {
  pool_->drawEntities();
}

template <class PoolType>
void EntityManager<PoolType>::updateEntitiesPosition() {
  pool_->updateEntitiesPosition();
}

template <class PoolType> PoolType& EntityManager<PoolType>::get_pool() {
  return *pool_;
}

template <class PoolType>
const PoolType& EntityManager<PoolType>::get_pool() const {
  return *pool_;
}